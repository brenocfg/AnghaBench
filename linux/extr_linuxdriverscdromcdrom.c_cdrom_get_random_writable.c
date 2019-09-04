#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rwrt_feature_desc {int dummy; } ;
struct packet_command {int* cmd; int quiet; } ;
struct feature_header {int dummy; } ;
struct cdrom_device_info {TYPE_1__* ops; } ;
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_2__ {int (* generic_packet ) (struct cdrom_device_info*,struct packet_command*) ;} ;

/* Variables and functions */
 int CDF_RWRT ; 
 int /*<<< orphan*/  CGC_DATA_READ ; 
 int GPCMD_GET_CONFIGURATION ; 
 int /*<<< orphan*/  init_cdrom_command (struct packet_command*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct rwrt_feature_desc*,char*,int) ; 
 int stub1 (struct cdrom_device_info*,struct packet_command*) ; 

__attribute__((used)) static int cdrom_get_random_writable(struct cdrom_device_info *cdi,
			      struct rwrt_feature_desc *rfd)
{
	struct packet_command cgc;
	char buffer[24];
	int ret;

	init_cdrom_command(&cgc, buffer, sizeof(buffer), CGC_DATA_READ);

	cgc.cmd[0] = GPCMD_GET_CONFIGURATION;	/* often 0x46 */
	cgc.cmd[3] = CDF_RWRT;			/* often 0x0020 */
	cgc.cmd[8] = sizeof(buffer);		/* often 0x18 */
	cgc.quiet = 1;

	if ((ret = cdi->ops->generic_packet(cdi, &cgc)))
		return ret;

	memcpy(rfd, &buffer[sizeof(struct feature_header)], sizeof (*rfd));
	return 0;
}