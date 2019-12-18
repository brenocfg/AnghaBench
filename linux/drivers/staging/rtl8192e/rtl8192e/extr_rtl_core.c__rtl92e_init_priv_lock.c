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
struct r8192_priv {int /*<<< orphan*/  mutex; int /*<<< orphan*/  rf_mutex; int /*<<< orphan*/  wx_mutex; int /*<<< orphan*/  ps_lock; int /*<<< orphan*/  rf_ps_lock; int /*<<< orphan*/  irq_th_lock; int /*<<< orphan*/  tx_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void _rtl92e_init_priv_lock(struct r8192_priv *priv)
{
	spin_lock_init(&priv->tx_lock);
	spin_lock_init(&priv->irq_th_lock);
	spin_lock_init(&priv->rf_ps_lock);
	spin_lock_init(&priv->ps_lock);
	mutex_init(&priv->wx_mutex);
	mutex_init(&priv->rf_mutex);
	mutex_init(&priv->mutex);
}