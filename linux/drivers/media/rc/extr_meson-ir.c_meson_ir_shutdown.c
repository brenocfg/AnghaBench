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
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct meson_ir {int /*<<< orphan*/  lock; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int DECODE_MODE_NEC ; 
 int /*<<< orphan*/  IR_DEC_REG0 ; 
 int /*<<< orphan*/  IR_DEC_REG1 ; 
 int /*<<< orphan*/  IR_DEC_REG2 ; 
 int /*<<< orphan*/  REG0_RATE_MASK ; 
 int /*<<< orphan*/  REG1_MODE_MASK ; 
 int REG1_MODE_SHIFT ; 
 int /*<<< orphan*/  REG2_MODE_MASK ; 
 int REG2_MODE_SHIFT ; 
 int /*<<< orphan*/  meson_ir_set_mask (struct meson_ir*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ of_device_is_compatible (struct device_node*,char*) ; 
 struct meson_ir* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void meson_ir_shutdown(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *node = dev->of_node;
	struct meson_ir *ir = platform_get_drvdata(pdev);
	unsigned long flags;

	spin_lock_irqsave(&ir->lock, flags);

	/*
	 * Set operation mode to NEC/hardware decoding to give
	 * bootloader a chance to power the system back on
	 */
	if (of_device_is_compatible(node, "amlogic,meson6-ir"))
		meson_ir_set_mask(ir, IR_DEC_REG1, REG1_MODE_MASK,
				  DECODE_MODE_NEC << REG1_MODE_SHIFT);
	else
		meson_ir_set_mask(ir, IR_DEC_REG2, REG2_MODE_MASK,
				  DECODE_MODE_NEC << REG2_MODE_SHIFT);

	/* Set rate to default value */
	meson_ir_set_mask(ir, IR_DEC_REG0, REG0_RATE_MASK, 0x13);

	spin_unlock_irqrestore(&ir->lock, flags);
}