#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLCR_PS_RST_CTRL_OFFSET ; 
 int /*<<< orphan*/  SLCR_REBOOT_STATUS_OFFSET ; 
 int /*<<< orphan*/  zynq_slcr_read (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zynq_slcr_write (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
int zynq_slcr_system_restart(struct notifier_block *nb,
			     unsigned long action, void *data)
{
	u32 reboot;

	/*
	 * Clear 0x0F000000 bits of reboot status register to workaround
	 * the FSBL not loading the bitstream after soft-reboot
	 * This is a temporary solution until we know more.
	 */
	zynq_slcr_read(&reboot, SLCR_REBOOT_STATUS_OFFSET);
	zynq_slcr_write(reboot & 0xF0FFFFFF, SLCR_REBOOT_STATUS_OFFSET);
	zynq_slcr_write(1, SLCR_PS_RST_CTRL_OFFSET);
	return 0;
}