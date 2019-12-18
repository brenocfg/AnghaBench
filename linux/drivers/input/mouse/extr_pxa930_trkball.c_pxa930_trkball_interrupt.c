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
struct pxa930_trkball {scalar_t__ mmio_base; struct input_dev* input; } ;
struct input_dev {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  REL_X ; 
 int /*<<< orphan*/  REL_Y ; 
 scalar_t__ TBCNTR ; 
 int TBCNTR_XM (int) ; 
 int TBCNTR_XP (int) ; 
 int TBCNTR_YM (int) ; 
 int TBCNTR_YP (int) ; 
 scalar_t__ TBSBC ; 
 int /*<<< orphan*/  TBSBC_TBSBC ; 
 int __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writel (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  input_report_rel (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 

__attribute__((used)) static irqreturn_t pxa930_trkball_interrupt(int irq, void *dev_id)
{
	struct pxa930_trkball *trkball = dev_id;
	struct input_dev *input = trkball->input;
	int tbcntr, x, y;

	/* According to the spec software must read TBCNTR twice:
	 * if the read value is the same, the reading is valid
	 */
	tbcntr = __raw_readl(trkball->mmio_base + TBCNTR);

	if (tbcntr == __raw_readl(trkball->mmio_base + TBCNTR)) {
		x = (TBCNTR_XP(tbcntr) - TBCNTR_XM(tbcntr)) / 2;
		y = (TBCNTR_YP(tbcntr) - TBCNTR_YM(tbcntr)) / 2;

		input_report_rel(input, REL_X, x);
		input_report_rel(input, REL_Y, y);
		input_sync(input);
	}

	__raw_writel(TBSBC_TBSBC, trkball->mmio_base + TBSBC);
	__raw_writel(0, trkball->mmio_base + TBSBC);

	return IRQ_HANDLED;
}