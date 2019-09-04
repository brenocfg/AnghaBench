#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct timer_list {int dummy; } ;
struct TYPE_5__ {int ctrl; } ;
struct TYPE_4__ {int quirk_suspend_irq; TYPE_2__ reg_timings; } ;
struct img_ir_priv {int /*<<< orphan*/  lock; TYPE_1__ hw; } ;
struct TYPE_6__ {int /*<<< orphan*/  suspend_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMG_IR_CONTROL ; 
 int IMG_IR_IRQ_EDGE ; 
 int /*<<< orphan*/  IMG_IR_IRQ_ENABLE ; 
 struct img_ir_priv* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 TYPE_3__ hw ; 
 int img_ir_read (struct img_ir_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  img_ir_write (struct img_ir_priv*,int /*<<< orphan*/ ,int) ; 
 struct img_ir_priv* priv ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void img_ir_suspend_timer(struct timer_list *t)
{
	struct img_ir_priv *priv = from_timer(priv, t, hw.suspend_timer);

	spin_lock_irq(&priv->lock);
	/*
	 * Don't overwrite enabled valid/match IRQs if they have already been
	 * changed by e.g. a filter change.
	 */
	if ((priv->hw.quirk_suspend_irq & IMG_IR_IRQ_EDGE) ==
				img_ir_read(priv, IMG_IR_IRQ_ENABLE))
		img_ir_write(priv, IMG_IR_IRQ_ENABLE,
					priv->hw.quirk_suspend_irq);
	/* enable */
	img_ir_write(priv, IMG_IR_CONTROL, priv->hw.reg_timings.ctrl);
	spin_unlock_irq(&priv->lock);
}