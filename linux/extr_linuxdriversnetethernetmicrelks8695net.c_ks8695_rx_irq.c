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
struct net_device {int dummy; } ;
struct ks8695_priv {int /*<<< orphan*/  rx_lock; int /*<<< orphan*/  napi; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ KS8695_INTEN ; 
 scalar_t__ KS8695_IRQ_VA ; 
 int /*<<< orphan*/  __napi_schedule (int /*<<< orphan*/ *) ; 
 int ks8695_get_rx_enable_bit (struct ks8695_priv*) ; 
 scalar_t__ napi_schedule_prep (int /*<<< orphan*/ *) ; 
 struct ks8695_priv* netdev_priv (struct net_device*) ; 
 unsigned long readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static irqreturn_t
ks8695_rx_irq(int irq, void *dev_id)
{
	struct net_device *ndev = (struct net_device *)dev_id;
	struct ks8695_priv *ksp = netdev_priv(ndev);

	spin_lock(&ksp->rx_lock);

	if (napi_schedule_prep(&ksp->napi)) {
		unsigned long status = readl(KS8695_IRQ_VA + KS8695_INTEN);
		unsigned long mask_bit = 1 << ks8695_get_rx_enable_bit(ksp);
		/*disable rx interrupt*/
		status &= ~mask_bit;
		writel(status , KS8695_IRQ_VA + KS8695_INTEN);
		__napi_schedule(&ksp->napi);
	}

	spin_unlock(&ksp->rx_lock);
	return IRQ_HANDLED;
}