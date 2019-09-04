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
struct pch_can_priv {int /*<<< orphan*/  napi; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  PCH_CAN_NONE ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 struct pch_can_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pch_can_int_pending (struct pch_can_priv*) ; 
 int /*<<< orphan*/  pch_can_set_int_enables (struct pch_can_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t pch_can_interrupt(int irq, void *dev_id)
{
	struct net_device *ndev = (struct net_device *)dev_id;
	struct pch_can_priv *priv = netdev_priv(ndev);

	if (!pch_can_int_pending(priv))
		return IRQ_NONE;

	pch_can_set_int_enables(priv, PCH_CAN_NONE);
	napi_schedule(&priv->napi);
	return IRQ_HANDLED;
}