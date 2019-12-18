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
struct TYPE_2__ {int /*<<< orphan*/  ctrl; int /*<<< orphan*/  timings; } ;
struct img_ir_priv_hw {scalar_t__ mode; TYPE_1__ reg_timings; } ;
struct img_ir_priv {struct img_ir_priv_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMG_IR_CONTROL ; 
 scalar_t__ IMG_IR_M_NORMAL ; 
 scalar_t__ IMG_IR_M_REPEATING ; 
 int /*<<< orphan*/  RC_FILTER_NORMAL ; 
 int /*<<< orphan*/  img_ir_write (struct img_ir_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  img_ir_write_timings (struct img_ir_priv*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void img_ir_end_repeat(struct img_ir_priv *priv)
{
	struct img_ir_priv_hw *hw = &priv->hw;
	if (hw->mode == IMG_IR_M_REPEATING) {
		/* switch to normal timings */
		img_ir_write(priv, IMG_IR_CONTROL, 0);
		hw->mode = IMG_IR_M_NORMAL;
		img_ir_write_timings(priv, &hw->reg_timings.timings,
				     RC_FILTER_NORMAL);
		img_ir_write(priv, IMG_IR_CONTROL, hw->reg_timings.ctrl);
	}
}