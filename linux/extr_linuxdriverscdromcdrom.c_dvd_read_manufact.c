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
typedef  int u_char ;
struct packet_command {int* cmd; } ;
struct cdrom_device_ops {int (* generic_packet ) (struct cdrom_device_info*,struct packet_command*) ;} ;
struct cdrom_device_info {struct cdrom_device_ops* ops; } ;
struct TYPE_4__ {int len; int /*<<< orphan*/  value; } ;
struct TYPE_5__ {int type; TYPE_1__ manufact; } ;
typedef  TYPE_2__ dvd_struct ;

/* Variables and functions */
 int /*<<< orphan*/  CD_WARNING ; 
 int /*<<< orphan*/  CGC_DATA_READ ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int GPCMD_READ_DVD_STRUCTURE ; 
 int /*<<< orphan*/  cd_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  init_cdrom_command (struct packet_command*,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 int stub1 (struct cdrom_device_info*,struct packet_command*) ; 

__attribute__((used)) static int dvd_read_manufact(struct cdrom_device_info *cdi, dvd_struct *s,
				struct packet_command *cgc)
{
	int ret = 0, size;
	u_char *buf;
	const struct cdrom_device_ops *cdo = cdi->ops;

	size = sizeof(s->manufact.value) + 4;

	buf = kmalloc(size, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	init_cdrom_command(cgc, buf, size, CGC_DATA_READ);
	cgc->cmd[0] = GPCMD_READ_DVD_STRUCTURE;
	cgc->cmd[7] = s->type;
	cgc->cmd[8] = size >> 8;
	cgc->cmd[9] = size & 0xff;

	ret = cdo->generic_packet(cdi, cgc);
	if (ret)
		goto out;

	s->manufact.len = buf[0] << 8 | buf[1];
	if (s->manufact.len < 0) {
		cd_dbg(CD_WARNING, "Received invalid manufacture info length (%d)\n",
		       s->manufact.len);
		ret = -EIO;
	} else {
		if (s->manufact.len > 2048) {
			cd_dbg(CD_WARNING, "Received invalid manufacture info length (%d): truncating to 2048\n",
			       s->manufact.len);
			s->manufact.len = 2048;
		}
		memcpy(s->manufact.value, &buf[4], s->manufact.len);
	}

out:
	kfree(buf);
	return ret;
}