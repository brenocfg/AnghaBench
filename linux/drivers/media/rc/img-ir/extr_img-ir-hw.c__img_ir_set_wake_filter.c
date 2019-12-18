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
struct img_ir_priv_hw {int /*<<< orphan*/  flags; struct img_ir_filter* filters; } ;
struct img_ir_priv {struct img_ir_priv_hw hw; } ;
struct img_ir_filter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMG_IR_F_WAKE ; 
 size_t RC_FILTER_WAKEUP ; 

__attribute__((used)) static void _img_ir_set_wake_filter(struct img_ir_priv *priv,
				    struct img_ir_filter *filter)
{
	struct img_ir_priv_hw *hw = &priv->hw;
	if (filter) {
		/* Enable wake, and copy filter for later */
		hw->filters[RC_FILTER_WAKEUP] = *filter;
		hw->flags |= IMG_IR_F_WAKE;
	} else {
		/* Disable wake */
		hw->flags &= ~IMG_IR_F_WAKE;
	}
}