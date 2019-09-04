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
struct mlx5_priv {int is_accum_events; int /*<<< orphan*/  ctx_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void delayed_event_start(struct mlx5_priv *priv)
{
	spin_lock_irq(&priv->ctx_lock);
	priv->is_accum_events = true;
	spin_unlock_irq(&priv->ctx_lock);
}