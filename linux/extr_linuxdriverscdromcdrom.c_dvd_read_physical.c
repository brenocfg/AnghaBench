#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct packet_command {int* cmd; int buflen; int quiet; } ;
struct dvd_layer {unsigned char book_version; unsigned char book_type; unsigned char min_rate; unsigned char disc_size; unsigned char layer_type; unsigned char track_path; unsigned char nlayers; unsigned char track_density; unsigned char linear_density; unsigned char start_sector; unsigned char end_sector; unsigned char end_sector_l0; unsigned char bca; } ;
struct cdrom_device_ops {int (* generic_packet ) (struct cdrom_device_info*,struct packet_command*) ;} ;
struct cdrom_device_info {struct cdrom_device_ops* ops; } ;
struct TYPE_4__ {int layer_num; struct dvd_layer* layer; } ;
struct TYPE_5__ {int type; TYPE_1__ physical; } ;
typedef  TYPE_2__ dvd_struct ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  CGC_DATA_READ ; 
 int DVD_LAYERS ; 
 int EINVAL ; 
 int GPCMD_READ_DVD_STRUCTURE ; 
 int /*<<< orphan*/  init_cdrom_command (struct packet_command*,unsigned char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct dvd_layer*,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct cdrom_device_info*,struct packet_command*) ; 

__attribute__((used)) static int dvd_read_physical(struct cdrom_device_info *cdi, dvd_struct *s,
				struct packet_command *cgc)
{
	unsigned char buf[21], *base;
	struct dvd_layer *layer;
	const struct cdrom_device_ops *cdo = cdi->ops;
	int ret, layer_num = s->physical.layer_num;

	if (layer_num >= DVD_LAYERS)
		return -EINVAL;

	init_cdrom_command(cgc, buf, sizeof(buf), CGC_DATA_READ);
	cgc->cmd[0] = GPCMD_READ_DVD_STRUCTURE;
	cgc->cmd[6] = layer_num;
	cgc->cmd[7] = s->type;
	cgc->cmd[9] = cgc->buflen & 0xff;

	/*
	 * refrain from reporting errors on non-existing layers (mainly)
	 */
	cgc->quiet = 1;

	ret = cdo->generic_packet(cdi, cgc);
	if (ret)
		return ret;

	base = &buf[4];
	layer = &s->physical.layer[layer_num];

	/*
	 * place the data... really ugly, but at least we won't have to
	 * worry about endianess in userspace.
	 */
	memset(layer, 0, sizeof(*layer));
	layer->book_version = base[0] & 0xf;
	layer->book_type = base[0] >> 4;
	layer->min_rate = base[1] & 0xf;
	layer->disc_size = base[1] >> 4;
	layer->layer_type = base[2] & 0xf;
	layer->track_path = (base[2] >> 4) & 1;
	layer->nlayers = (base[2] >> 5) & 3;
	layer->track_density = base[3] & 0xf;
	layer->linear_density = base[3] >> 4;
	layer->start_sector = base[5] << 16 | base[6] << 8 | base[7];
	layer->end_sector = base[9] << 16 | base[10] << 8 | base[11];
	layer->end_sector_l0 = base[13] << 16 | base[14] << 8 | base[15];
	layer->bca = base[16] >> 7;

	return 0;
}