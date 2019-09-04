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
typedef  size_t u8 ;
typedef  size_t u32 ;
struct pic32_ref_osc {size_t* parent_map; TYPE_1__* core; int /*<<< orphan*/  ctrl_reg; } ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK_TIMEOUT_US ; 
 size_t REFO_ACTIVE ; 
 size_t REFO_SEL_MASK ; 
 size_t REFO_SEL_SHIFT ; 
 int /*<<< orphan*/  clk_hw_get_name (struct clk_hw*) ; 
 struct pic32_ref_osc* clkhw_to_refosc (struct clk_hw*) ; 
 int /*<<< orphan*/  pic32_syskey_unlock () ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 size_t readl (int /*<<< orphan*/ ) ; 
 int readl_poll_timeout (int /*<<< orphan*/ ,size_t,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int roclk_set_parent(struct clk_hw *hw, u8 index)
{
	struct pic32_ref_osc *refo = clkhw_to_refosc(hw);
	unsigned long flags;
	u32 v;
	int err;

	if (refo->parent_map)
		index = refo->parent_map[index];

	/* wait until ACTIVE bit is zero or timeout */
	err = readl_poll_timeout(refo->ctrl_reg, v, !(v & REFO_ACTIVE),
				 1, LOCK_TIMEOUT_US);
	if (err) {
		pr_err("%s: poll failed, clk active\n", clk_hw_get_name(hw));
		return err;
	}

	spin_lock_irqsave(&refo->core->reg_lock, flags);

	pic32_syskey_unlock();

	/* calculate & apply new */
	v = readl(refo->ctrl_reg);
	v &= ~(REFO_SEL_MASK << REFO_SEL_SHIFT);
	v |= index << REFO_SEL_SHIFT;

	writel(v, refo->ctrl_reg);

	spin_unlock_irqrestore(&refo->core->reg_lock, flags);

	return 0;
}