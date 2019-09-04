#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct timer_list {int dummy; } ;
struct TYPE_3__ {scalar_t__ rdev; } ;
struct img_ir_priv {int /*<<< orphan*/  lock; TYPE_1__ raw; } ;
struct TYPE_4__ {int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 struct img_ir_priv* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  img_ir_refresh_raw (struct img_ir_priv*,int /*<<< orphan*/ ) ; 
 struct img_ir_priv* priv ; 
 TYPE_2__ raw ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void img_ir_echo_timer(struct timer_list *t)
{
	struct img_ir_priv *priv = from_timer(priv, t, raw.timer);

	spin_lock_irq(&priv->lock);

	/* check not removing */
	if (priv->raw.rdev)
		/*
		 * It's safe to pass irq_status=0 since it's only used to check
		 * for double edges.
		 */
		img_ir_refresh_raw(priv, 0);

	spin_unlock_irq(&priv->lock);
}