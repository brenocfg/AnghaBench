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
 int DV3318_DETECT_EN ; 
 int DV3318_OCP_INT_EN ; 
 int /*<<< orphan*/  FPDCTL ; 
 int OC_POWER_DOWN ; 
 int /*<<< orphan*/  REG_DV3318_OCPCTL ; 
 int /*<<< orphan*/  REG_OCPCTL ; 
 int SDVIO_DETECT_EN ; 
 int SDVIO_OCP_INT_EN ; 
 int SD_DETECT_EN ; 
 int SD_OCP_INT_EN ; 
 int /*<<< orphan*/  rtsx_pci_write_register (struct rtsx_pcr*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void rts5260_enable_ocp(struct rtsx_pcr *pcr)
{
	u8 val = 0;

	rtsx_pci_write_register(pcr, FPDCTL, OC_POWER_DOWN, 0);

	val = SD_OCP_INT_EN | SD_DETECT_EN;
	val |= SDVIO_OCP_INT_EN | SDVIO_DETECT_EN;
	rtsx_pci_write_register(pcr, REG_OCPCTL, 0xFF, val);
	rtsx_pci_write_register(pcr, REG_DV3318_OCPCTL,
				DV3318_DETECT_EN | DV3318_OCP_INT_EN,
				DV3318_DETECT_EN | DV3318_OCP_INT_EN);
}