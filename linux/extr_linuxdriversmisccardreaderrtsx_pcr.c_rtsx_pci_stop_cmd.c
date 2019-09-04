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
struct rtsx_pcr {TYPE_1__* ops; } ;
struct TYPE_2__ {void (* stop_cmd ) (struct rtsx_pcr*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DMACTL ; 
 int /*<<< orphan*/  RBCTL ; 
 int /*<<< orphan*/  RTSX_HCBCTLR ; 
 int /*<<< orphan*/  RTSX_HDBCTLR ; 
 int /*<<< orphan*/  STOP_CMD ; 
 int /*<<< orphan*/  STOP_DMA ; 
 int /*<<< orphan*/  rtsx_pci_write_register (struct rtsx_pcr*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rtsx_pci_writel (struct rtsx_pcr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void stub1 (struct rtsx_pcr*) ; 

void rtsx_pci_stop_cmd(struct rtsx_pcr *pcr)
{
	if (pcr->ops->stop_cmd)
		return pcr->ops->stop_cmd(pcr);

	rtsx_pci_writel(pcr, RTSX_HCBCTLR, STOP_CMD);
	rtsx_pci_writel(pcr, RTSX_HDBCTLR, STOP_DMA);

	rtsx_pci_write_register(pcr, DMACTL, 0x80, 0x80);
	rtsx_pci_write_register(pcr, RBCTL, 0x80, 0x80);
}