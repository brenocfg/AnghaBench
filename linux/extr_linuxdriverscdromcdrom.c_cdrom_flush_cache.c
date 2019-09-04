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
struct packet_command {int timeout; int /*<<< orphan*/ * cmd; } ;
struct cdrom_device_info {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* generic_packet ) (struct cdrom_device_info*,struct packet_command*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CGC_DATA_NONE ; 
 int /*<<< orphan*/  GPCMD_FLUSH_CACHE ; 
 int HZ ; 
 int /*<<< orphan*/  init_cdrom_command (struct packet_command*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct cdrom_device_info*,struct packet_command*) ; 

__attribute__((used)) static int cdrom_flush_cache(struct cdrom_device_info *cdi)
{
	struct packet_command cgc;

	init_cdrom_command(&cgc, NULL, 0, CGC_DATA_NONE);
	cgc.cmd[0] = GPCMD_FLUSH_CACHE;

	cgc.timeout = 5 * 60 * HZ;

	return cdi->ops->generic_packet(cdi, &cgc);
}