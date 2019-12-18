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
struct c_can_priv {int (* read_reg ) (struct c_can_priv*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  napi; int /*<<< orphan*/  sie_pending; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  C_CAN_INT_REG ; 
 int INT_STS_PENDING ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  c_can_irq_control (struct c_can_priv*,int) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 struct c_can_priv* netdev_priv (struct net_device*) ; 
 int stub1 (struct c_can_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t c_can_isr(int irq, void *dev_id)
{
	struct net_device *dev = (struct net_device *)dev_id;
	struct c_can_priv *priv = netdev_priv(dev);
	int reg_int;

	reg_int = priv->read_reg(priv, C_CAN_INT_REG);
	if (!reg_int)
		return IRQ_NONE;

	/* save for later use */
	if (reg_int & INT_STS_PENDING)
		atomic_set(&priv->sie_pending, 1);

	/* disable all interrupts and schedule the NAPI */
	c_can_irq_control(priv, false);
	napi_schedule(&priv->napi);

	return IRQ_HANDLED;
}