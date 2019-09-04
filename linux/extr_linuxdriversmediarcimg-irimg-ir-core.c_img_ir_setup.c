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
struct img_ir_priv {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMG_IR_IRQ_ENABLE ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  img_ir_setup_hw (struct img_ir_priv*) ; 
 int /*<<< orphan*/  img_ir_setup_raw (struct img_ir_priv*) ; 
 int /*<<< orphan*/  img_ir_write (struct img_ir_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void img_ir_setup(struct img_ir_priv *priv)
{
	/* start off with interrupts disabled */
	img_ir_write(priv, IMG_IR_IRQ_ENABLE, 0);

	img_ir_setup_raw(priv);
	img_ir_setup_hw(priv);

	if (!IS_ERR(priv->clk))
		clk_prepare_enable(priv->clk);
}