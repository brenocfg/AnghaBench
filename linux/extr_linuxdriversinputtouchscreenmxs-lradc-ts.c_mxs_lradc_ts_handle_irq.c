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
typedef  unsigned long u32 ;
struct mxs_lradc_ts {scalar_t__ base; int /*<<< orphan*/  lock; struct mxs_lradc* lradc; } ;
struct mxs_lradc {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ LRADC_CTRL1 ; 
 unsigned long LRADC_CTRL1_LRADC_IRQ (int /*<<< orphan*/ ) ; 
 unsigned long LRADC_CTRL1_TOUCH_DETECT_IRQ ; 
 scalar_t__ STMP_OFFSET_REG_CLR ; 
 int /*<<< orphan*/  TOUCHSCREEN_VCHANNEL1 ; 
 int /*<<< orphan*/  TOUCHSCREEN_VCHANNEL2 ; 
 int /*<<< orphan*/  mxs_lradc_handle_touch (struct mxs_lradc_ts*) ; 
 unsigned long mxs_lradc_irq_mask (struct mxs_lradc*) ; 
 unsigned long readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static irqreturn_t mxs_lradc_ts_handle_irq(int irq, void *data)
{
	struct mxs_lradc_ts *ts = data;
	struct mxs_lradc *lradc = ts->lradc;
	unsigned long reg = readl(ts->base + LRADC_CTRL1);
	u32 clr_irq = mxs_lradc_irq_mask(lradc);
	const u32 ts_irq_mask =
		LRADC_CTRL1_TOUCH_DETECT_IRQ |
		LRADC_CTRL1_LRADC_IRQ(TOUCHSCREEN_VCHANNEL1) |
		LRADC_CTRL1_LRADC_IRQ(TOUCHSCREEN_VCHANNEL2);
	unsigned long flags;

	if (!(reg & mxs_lradc_irq_mask(lradc)))
		return IRQ_NONE;

	if (reg & ts_irq_mask) {
		spin_lock_irqsave(&ts->lock, flags);
		mxs_lradc_handle_touch(ts);
		spin_unlock_irqrestore(&ts->lock, flags);
		/* Make sure we don't clear the next conversion's interrupt. */
		clr_irq &= ~(LRADC_CTRL1_LRADC_IRQ(TOUCHSCREEN_VCHANNEL1) |
				LRADC_CTRL1_LRADC_IRQ(TOUCHSCREEN_VCHANNEL2));
		writel(reg & clr_irq,
		       ts->base + LRADC_CTRL1 + STMP_OFFSET_REG_CLR);
	}

	return IRQ_HANDLED;
}