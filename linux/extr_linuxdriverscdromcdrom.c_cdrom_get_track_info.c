#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  track_information_length; } ;
typedef  TYPE_1__ track_information ;
struct packet_command {int* cmd; int quiet; int buflen; } ;
struct cdrom_device_ops {int (* generic_packet ) (struct cdrom_device_info*,struct packet_command*) ;} ;
struct cdrom_device_info {struct cdrom_device_ops* ops; } ;
typedef  int __u8 ;
typedef  int __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  CGC_DATA_READ ; 
 int GPCMD_READ_TRACK_RZONE_INFO ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_cdrom_command (struct packet_command*,TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int stub1 (struct cdrom_device_info*,struct packet_command*) ; 
 int stub2 (struct cdrom_device_info*,struct packet_command*) ; 

__attribute__((used)) static int cdrom_get_track_info(struct cdrom_device_info *cdi,
				__u16 track, __u8 type, track_information *ti)
{
	const struct cdrom_device_ops *cdo = cdi->ops;
	struct packet_command cgc;
	int ret, buflen;

	init_cdrom_command(&cgc, ti, 8, CGC_DATA_READ);
	cgc.cmd[0] = GPCMD_READ_TRACK_RZONE_INFO;
	cgc.cmd[1] = type & 3;
	cgc.cmd[4] = (track & 0xff00) >> 8;
	cgc.cmd[5] = track & 0xff;
	cgc.cmd[8] = 8;
	cgc.quiet = 1;

	ret = cdo->generic_packet(cdi, &cgc);
	if (ret)
		return ret;

	buflen = be16_to_cpu(ti->track_information_length) +
		sizeof(ti->track_information_length);

	if (buflen > sizeof(track_information))
		buflen = sizeof(track_information);

	cgc.cmd[8] = cgc.buflen = buflen;
	ret = cdo->generic_packet(cdi, &cgc);
	if (ret)
		return ret;

	/* return actual fill size */
	return buflen;
}