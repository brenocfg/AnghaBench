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
typedef  int u32 ;
struct ethsw_core {int /*<<< orphan*/  dpsw_handle; int /*<<< orphan*/  mc_io; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int DPSW_IRQ_EVENT_LINK_CHANGED ; 
 int /*<<< orphan*/  DPSW_IRQ_INDEX_IF ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct ethsw_core* dev_get_drvdata (struct device*) ; 
 int dpsw_clear_irq_status (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int dpsw_get_irq_status (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ethsw_links_state_update (struct ethsw_core*) ; 

__attribute__((used)) static irqreturn_t ethsw_irq0_handler_thread(int irq_num, void *arg)
{
	struct device *dev = (struct device *)arg;
	struct ethsw_core *ethsw = dev_get_drvdata(dev);

	/* Mask the events and the if_id reserved bits to be cleared on read */
	u32 status = DPSW_IRQ_EVENT_LINK_CHANGED | 0xFFFF0000;
	int err;

	err = dpsw_get_irq_status(ethsw->mc_io, 0, ethsw->dpsw_handle,
				  DPSW_IRQ_INDEX_IF, &status);
	if (err) {
		dev_err(dev, "Can't get irq status (err %d)\n", err);

		err = dpsw_clear_irq_status(ethsw->mc_io, 0, ethsw->dpsw_handle,
					    DPSW_IRQ_INDEX_IF, 0xFFFFFFFF);
		if (err)
			dev_err(dev, "Can't clear irq status (err %d)\n", err);
		goto out;
	}

	if (status & DPSW_IRQ_EVENT_LINK_CHANGED)
		ethsw_links_state_update(ethsw);

out:
	return IRQ_HANDLED;
}