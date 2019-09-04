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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  rdev; } ;
struct img_ir_priv {int /*<<< orphan*/  lock; TYPE_1__ raw; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMG_IR_IRQ_CLEAR ; 
 int /*<<< orphan*/  IMG_IR_IRQ_EDGE ; 
 int /*<<< orphan*/  IMG_IR_IRQ_ENABLE ; 
 int /*<<< orphan*/  img_ir_read (struct img_ir_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  img_ir_write (struct img_ir_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void img_ir_setup_raw(struct img_ir_priv *priv)
{
	u32 irq_en;

	if (!priv->raw.rdev)
		return;

	/* clear and enable edge interrupts */
	spin_lock_irq(&priv->lock);
	irq_en = img_ir_read(priv, IMG_IR_IRQ_ENABLE);
	irq_en |= IMG_IR_IRQ_EDGE;
	img_ir_write(priv, IMG_IR_IRQ_CLEAR, IMG_IR_IRQ_EDGE);
	img_ir_write(priv, IMG_IR_IRQ_ENABLE, irq_en);
	spin_unlock_irq(&priv->lock);
}