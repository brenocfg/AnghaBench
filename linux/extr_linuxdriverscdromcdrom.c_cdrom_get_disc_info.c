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
struct packet_command {int* cmd; int buflen; int quiet; } ;
struct cdrom_device_ops {int (* generic_packet ) (struct cdrom_device_info*,struct packet_command*) ;} ;
struct cdrom_device_info {struct cdrom_device_ops* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  disc_information_length; } ;
typedef  TYPE_1__ disc_information ;

/* Variables and functions */
 int /*<<< orphan*/  CGC_DATA_READ ; 
 int GPCMD_READ_DISC_INFO ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_cdrom_command (struct packet_command*,TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int stub1 (struct cdrom_device_info*,struct packet_command*) ; 
 int stub2 (struct cdrom_device_info*,struct packet_command*) ; 

__attribute__((used)) static int cdrom_get_disc_info(struct cdrom_device_info *cdi,
			       disc_information *di)
{
	const struct cdrom_device_ops *cdo = cdi->ops;
	struct packet_command cgc;
	int ret, buflen;

	/* set up command and get the disc info */
	init_cdrom_command(&cgc, di, sizeof(*di), CGC_DATA_READ);
	cgc.cmd[0] = GPCMD_READ_DISC_INFO;
	cgc.cmd[8] = cgc.buflen = 2;
	cgc.quiet = 1;

	ret = cdo->generic_packet(cdi, &cgc);
	if (ret)
		return ret;

	/* not all drives have the same disc_info length, so requeue
	 * packet with the length the drive tells us it can supply
	 */
	buflen = be16_to_cpu(di->disc_information_length) +
		sizeof(di->disc_information_length);

	if (buflen > sizeof(disc_information))
		buflen = sizeof(disc_information);

	cgc.cmd[8] = cgc.buflen = buflen;
	ret = cdo->generic_packet(cdi, &cgc);
	if (ret)
		return ret;

	/* return actual fill size */
	return buflen;
}