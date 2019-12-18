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
struct rc_dev {int dummy; } ;
struct img_ir_priv_hw {int /*<<< orphan*/  clk_nb; struct rc_dev* rdev; } ;
struct img_ir_priv {int /*<<< orphan*/  clk; struct img_ir_priv_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_notifier_unregister (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  img_ir_set_decoder (struct img_ir_priv*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rc_unregister_device (struct rc_dev*) ; 

void img_ir_remove_hw(struct img_ir_priv *priv)
{
	struct img_ir_priv_hw *hw = &priv->hw;
	struct rc_dev *rdev = hw->rdev;
	if (!rdev)
		return;
	img_ir_set_decoder(priv, NULL, 0);
	hw->rdev = NULL;
	rc_unregister_device(rdev);
#ifdef CONFIG_COMMON_CLK
	if (!IS_ERR(priv->clk))
		clk_notifier_unregister(priv->clk, &hw->clk_nb);
#endif
}