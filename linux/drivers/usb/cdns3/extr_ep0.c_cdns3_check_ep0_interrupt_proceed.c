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
typedef  int u32 ;
struct cdns3_device {int wait_for_setup; int ep0_data_dir; int /*<<< orphan*/  setup_pending; TYPE_1__* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  ep_sts; } ;

/* Variables and functions */
 int EP_STS_DESCMIS ; 
 int EP_STS_IOC ; 
 int EP_STS_ISP ; 
 int EP_STS_SETUP ; 
 int /*<<< orphan*/  __pending_setup_status_handler (struct cdns3_device*) ; 
 int /*<<< orphan*/  cdns3_allow_enable_l1 (struct cdns3_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdns3_ep0_setup_phase (struct cdns3_device*) ; 
 int /*<<< orphan*/  cdns3_prepare_setup_packet (struct cdns3_device*) ; 
 int /*<<< orphan*/  cdns3_select_ep (struct cdns3_device*,int) ; 
 int /*<<< orphan*/  cdns3_transfer_completed (struct cdns3_device*) ; 
 int readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_cdns3_ep0_irq (struct cdns3_device*,int) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

void cdns3_check_ep0_interrupt_proceed(struct cdns3_device *priv_dev, int dir)
{
	u32 ep_sts_reg;

	cdns3_select_ep(priv_dev, dir);

	ep_sts_reg = readl(&priv_dev->regs->ep_sts);
	writel(ep_sts_reg, &priv_dev->regs->ep_sts);

	trace_cdns3_ep0_irq(priv_dev, ep_sts_reg);

	__pending_setup_status_handler(priv_dev);

	if (ep_sts_reg & EP_STS_SETUP)
		priv_dev->wait_for_setup = 1;

	if (priv_dev->wait_for_setup && ep_sts_reg & EP_STS_IOC) {
		priv_dev->wait_for_setup = 0;
		cdns3_allow_enable_l1(priv_dev, 0);
		cdns3_ep0_setup_phase(priv_dev);
	} else if ((ep_sts_reg & EP_STS_IOC) || (ep_sts_reg & EP_STS_ISP)) {
		priv_dev->ep0_data_dir = dir;
		cdns3_transfer_completed(priv_dev);
	}

	if (ep_sts_reg & EP_STS_DESCMIS) {
		if (dir == 0 && !priv_dev->setup_pending)
			cdns3_prepare_setup_packet(priv_dev);
	}
}