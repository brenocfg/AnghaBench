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
struct mcde {int regs; int /*<<< orphan*/  dev; int /*<<< orphan*/  flow_lock; scalar_t__ flow_active; } ;
typedef  enum mcde_fifo { ____Placeholder_mcde_fifo } mcde_fifo ;

/* Variables and functions */
 int MCDE_CRA0 ; 
 int MCDE_CRB0 ; 
 int MCDE_CRX0_FLOEN ; 
#define  MCDE_FIFO_A 129 
#define  MCDE_FIFO_B 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,char) ; 
 int readl (int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  writel (int,int) ; 

__attribute__((used)) static void mcde_disable_fifo(struct mcde *mcde, enum mcde_fifo fifo,
			      bool wait_for_drain)
{
	int timeout = 100;
	u32 val;
	u32 cr;

	switch (fifo) {
	case MCDE_FIFO_A:
		cr = MCDE_CRA0;
		break;
	case MCDE_FIFO_B:
		cr = MCDE_CRB0;
		break;
	default:
		dev_err(mcde->dev, "cannot disable FIFO %c\n",
			'A' + fifo);
		return;
	}

	spin_lock(&mcde->flow_lock);
	val = readl(mcde->regs + cr);
	val &= ~MCDE_CRX0_FLOEN;
	writel(val, mcde->regs + cr);
	mcde->flow_active = 0;
	spin_unlock(&mcde->flow_lock);

	if (!wait_for_drain)
		return;

	/* Check that we really drained and stopped the flow */
	while (readl(mcde->regs + cr) & MCDE_CRX0_FLOEN) {
		usleep_range(1000, 1500);
		if (!--timeout) {
			dev_err(mcde->dev,
				"FIFO timeout while clearing FIFO %c\n",
				'A' + fifo);
			return;
		}
	}
}