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
typedef  int /*<<< orphan*/  u8 ;
struct rtsx_pcr {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* get_ocpstat ) (struct rtsx_pcr*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  REG_OCPSTAT ; 
 int rtsx_pci_read_register (struct rtsx_pcr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub1 (struct rtsx_pcr*,int /*<<< orphan*/ *) ; 

int rtsx_pci_get_ocpstat(struct rtsx_pcr *pcr, u8 *val)
{
	if (pcr->ops->get_ocpstat)
		return pcr->ops->get_ocpstat(pcr, val);
	else
		return rtsx_pci_read_register(pcr, REG_OCPSTAT, val);
}