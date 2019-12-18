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
struct rtsx_pcr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FUNC_FORCE_CTL ; 
 int FUNC_FORCE_UPME_XMT_DBG ; 
 int /*<<< orphan*/  PCLK_CTL ; 
 int PME_DEBUG_0 ; 
 int /*<<< orphan*/  PM_CLK_FORCE_CTL ; 
 int /*<<< orphan*/  PM_EVENT_DEBUG ; 
 int /*<<< orphan*/  rts5227_extra_init_hw (struct rtsx_pcr*) ; 
 int /*<<< orphan*/  rtsx_pci_write_register (struct rtsx_pcr*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int rts522a_extra_init_hw(struct rtsx_pcr *pcr)
{
	rts5227_extra_init_hw(pcr);

	rtsx_pci_write_register(pcr, FUNC_FORCE_CTL, FUNC_FORCE_UPME_XMT_DBG,
		FUNC_FORCE_UPME_XMT_DBG);
	rtsx_pci_write_register(pcr, PCLK_CTL, 0x04, 0x04);
	rtsx_pci_write_register(pcr, PM_EVENT_DEBUG, PME_DEBUG_0, PME_DEBUG_0);
	rtsx_pci_write_register(pcr, PM_CLK_FORCE_CTL, 0xFF, 0x11);

	return 0;
}