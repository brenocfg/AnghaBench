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
typedef  scalar_t__ u32 ;
struct mcde {int /*<<< orphan*/  flow_lock; int /*<<< orphan*/  flow_active; scalar_t__ regs; int /*<<< orphan*/  dev; } ;
typedef  enum mcde_fifo { ____Placeholder_mcde_fifo } mcde_fifo ;

/* Variables and functions */
 scalar_t__ MCDE_CRA0 ; 
 scalar_t__ MCDE_CRB0 ; 
 scalar_t__ MCDE_CRX0_FLOEN ; 
#define  MCDE_FIFO_A 129 
#define  MCDE_FIFO_B 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,char) ; 
 scalar_t__ readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void mcde_enable_fifo(struct mcde *mcde, enum mcde_fifo fifo)
{
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
		dev_err(mcde->dev, "cannot enable FIFO %c\n",
			'A' + fifo);
		return;
	}

	spin_lock(&mcde->flow_lock);
	val = readl(mcde->regs + cr);
	val |= MCDE_CRX0_FLOEN;
	writel(val, mcde->regs + cr);
	mcde->flow_active++;
	spin_unlock(&mcde->flow_lock);
}