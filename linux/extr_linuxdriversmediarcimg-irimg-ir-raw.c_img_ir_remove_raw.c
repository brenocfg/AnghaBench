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
typedef  int /*<<< orphan*/  u32 ;
struct rc_dev {int dummy; } ;
struct img_ir_priv_raw {int /*<<< orphan*/  timer; struct rc_dev* rdev; } ;
struct img_ir_priv {int /*<<< orphan*/  lock; struct img_ir_priv_raw raw; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMG_IR_IRQ_CLEAR ; 
 int /*<<< orphan*/  IMG_IR_IRQ_EDGE ; 
 int /*<<< orphan*/  IMG_IR_IRQ_ENABLE ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  img_ir_read (struct img_ir_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  img_ir_write (struct img_ir_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rc_unregister_device (struct rc_dev*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void img_ir_remove_raw(struct img_ir_priv *priv)
{
	struct img_ir_priv_raw *raw = &priv->raw;
	struct rc_dev *rdev = raw->rdev;
	u32 irq_en;

	if (!rdev)
		return;

	/* switch off and disable raw (edge) interrupts */
	spin_lock_irq(&priv->lock);
	raw->rdev = NULL;
	irq_en = img_ir_read(priv, IMG_IR_IRQ_ENABLE);
	irq_en &= ~IMG_IR_IRQ_EDGE;
	img_ir_write(priv, IMG_IR_IRQ_ENABLE, irq_en);
	img_ir_write(priv, IMG_IR_IRQ_CLEAR, IMG_IR_IRQ_EDGE);
	spin_unlock_irq(&priv->lock);

	rc_unregister_device(rdev);

	del_timer_sync(&raw->timer);
}