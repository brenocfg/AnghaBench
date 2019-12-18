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
typedef  int u8 ;
struct rtsx_pcr {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* disable_ocp ) (struct rtsx_pcr*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FPDCTL ; 
 int OC_POWER_DOWN ; 
 int /*<<< orphan*/  REG_OCPCTL ; 
 int SD_DETECT_EN ; 
 int SD_OCP_INT_EN ; 
 int /*<<< orphan*/  rtsx_pci_write_register (struct rtsx_pcr*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub1 (struct rtsx_pcr*) ; 

void rtsx_pci_disable_ocp(struct rtsx_pcr *pcr)
{
	u8 mask = SD_OCP_INT_EN | SD_DETECT_EN;

	if (pcr->ops->disable_ocp) {
		pcr->ops->disable_ocp(pcr);
	} else {
		rtsx_pci_write_register(pcr, REG_OCPCTL, mask, 0);
		rtsx_pci_write_register(pcr, FPDCTL, OC_POWER_DOWN,
				OC_POWER_DOWN);
	}
}