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
typedef  int u8 ;
struct rtsx_pcr {int dummy; } ;

/* Variables and functions */
 int DV3318_OCP_CLR ; 
 int DV3318_OCP_INT_CLR ; 
 int /*<<< orphan*/  REG_DV3318_OCPCTL ; 
 int /*<<< orphan*/  REG_OCPCTL ; 
 int SD_OCP_INT_CLR ; 
 int SD_OC_CLR ; 
 int /*<<< orphan*/  rtsx_pci_write_register (struct rtsx_pcr*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void rts5260_clear_ocpstat(struct rtsx_pcr *pcr)
{
	u8 mask = 0;
	u8 val = 0;

	mask = SD_OCP_INT_CLR | SD_OC_CLR;
	val = SD_OCP_INT_CLR | SD_OC_CLR;

	rtsx_pci_write_register(pcr, REG_OCPCTL, mask, val);
	rtsx_pci_write_register(pcr, REG_DV3318_OCPCTL,
				DV3318_OCP_INT_CLR | DV3318_OCP_CLR,
				DV3318_OCP_INT_CLR | DV3318_OCP_CLR);
	udelay(10);
	rtsx_pci_write_register(pcr, REG_OCPCTL, mask, 0);
	rtsx_pci_write_register(pcr, REG_DV3318_OCPCTL,
				DV3318_OCP_INT_CLR | DV3318_OCP_CLR, 0);
}