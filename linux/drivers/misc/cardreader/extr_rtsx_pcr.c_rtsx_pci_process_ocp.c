#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  ocp_en; } ;
struct rtsx_pcr {int ocp_stat; TYPE_2__ option; TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* process_ocp ) (struct rtsx_pcr*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_OE ; 
 int /*<<< orphan*/  RTSX_SD_CARD ; 
 int SD_OC_EVER ; 
 int SD_OC_NOW ; 
 int /*<<< orphan*/  SD_OUTPUT_EN ; 
 int /*<<< orphan*/  rtsx_pci_card_power_off (struct rtsx_pcr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtsx_pci_clear_ocpstat (struct rtsx_pcr*) ; 
 int /*<<< orphan*/  rtsx_pci_get_ocpstat (struct rtsx_pcr*,int*) ; 
 int /*<<< orphan*/  rtsx_pci_write_register (struct rtsx_pcr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct rtsx_pcr*) ; 

__attribute__((used)) static void rtsx_pci_process_ocp(struct rtsx_pcr *pcr)
{
	if (pcr->ops->process_ocp) {
		pcr->ops->process_ocp(pcr);
	} else {
		if (!pcr->option.ocp_en)
			return;
		rtsx_pci_get_ocpstat(pcr, &pcr->ocp_stat);
		if (pcr->ocp_stat & (SD_OC_NOW | SD_OC_EVER)) {
			rtsx_pci_card_power_off(pcr, RTSX_SD_CARD);
			rtsx_pci_write_register(pcr, CARD_OE, SD_OUTPUT_EN, 0);
			rtsx_pci_clear_ocpstat(pcr);
			pcr->ocp_stat = 0;
		}
	}
}