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
struct TYPE_2__ {int /*<<< orphan*/  ocp_en; } ;
struct rtsx_pcr {int ocp_stat; int ocp_stat2; TYPE_1__ option; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_OE ; 
 int DV3318_OCP_EVER ; 
 int DV3318_OCP_NOW ; 
 int /*<<< orphan*/  RTSX_SD_CARD ; 
 int SD_OC_EVER ; 
 int SD_OC_NOW ; 
 int /*<<< orphan*/  SD_OUTPUT_EN ; 
 int /*<<< orphan*/  rts5260_get_ocpstat2 (struct rtsx_pcr*,int*) ; 
 int /*<<< orphan*/  rtsx_pci_card_power_off (struct rtsx_pcr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtsx_pci_clear_ocpstat (struct rtsx_pcr*) ; 
 int /*<<< orphan*/  rtsx_pci_get_ocpstat (struct rtsx_pcr*,int*) ; 
 int /*<<< orphan*/  rtsx_pci_write_register (struct rtsx_pcr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rts5260_process_ocp(struct rtsx_pcr *pcr)
{
	if (!pcr->option.ocp_en)
		return;

	rtsx_pci_get_ocpstat(pcr, &pcr->ocp_stat);
	rts5260_get_ocpstat2(pcr, &pcr->ocp_stat2);

	if ((pcr->ocp_stat & (SD_OC_NOW | SD_OC_EVER)) ||
		(pcr->ocp_stat2 & (DV3318_OCP_NOW | DV3318_OCP_EVER))) {
		rtsx_pci_card_power_off(pcr, RTSX_SD_CARD);
		rtsx_pci_write_register(pcr, CARD_OE, SD_OUTPUT_EN, 0);
		rtsx_pci_clear_ocpstat(pcr);
		pcr->ocp_stat = 0;
		pcr->ocp_stat2 = 0;
	}

}