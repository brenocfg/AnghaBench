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
typedef  enum reboot_mode { ____Placeholder_reboot_mode } reboot_mode ;

/* Variables and functions */
 int IOP13XX_WDTCR_IB_RESET ; 
 int IOP13XX_WDTSR_WRITE_EN ; 
 int IOP_WDTCR_EN ; 
 int IOP_WDTCR_EN_ARM ; 
 int /*<<< orphan*/  write_wdtcr (int) ; 
 int /*<<< orphan*/  write_wdtsr (int) ; 

void iop13xx_restart(enum reboot_mode mode, const char *cmd)
{
	/*
	 * Reset the internal bus (warning both cores are reset)
	 */
	write_wdtcr(IOP_WDTCR_EN_ARM);
	write_wdtcr(IOP_WDTCR_EN);
	write_wdtsr(IOP13XX_WDTSR_WRITE_EN | IOP13XX_WDTCR_IB_RESET);
	write_wdtcr(0x1000);
}