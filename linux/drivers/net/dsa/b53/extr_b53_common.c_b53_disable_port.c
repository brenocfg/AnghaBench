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
typedef  int u8 ;
struct dsa_switch {struct b53_device* priv; } ;
struct b53_device {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* irq_disable ) (struct b53_device*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  B53_CTRL_PAGE ; 
 int /*<<< orphan*/  B53_PORT_CTRL (int) ; 
 int PORT_CTRL_RX_DISABLE ; 
 int PORT_CTRL_TX_DISABLE ; 
 int /*<<< orphan*/  b53_read8 (struct b53_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  b53_write8 (struct b53_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct b53_device*,int) ; 

void b53_disable_port(struct dsa_switch *ds, int port)
{
	struct b53_device *dev = ds->priv;
	u8 reg;

	/* Disable Tx/Rx for the port */
	b53_read8(dev, B53_CTRL_PAGE, B53_PORT_CTRL(port), &reg);
	reg |= PORT_CTRL_RX_DISABLE | PORT_CTRL_TX_DISABLE;
	b53_write8(dev, B53_CTRL_PAGE, B53_PORT_CTRL(port), reg);

	if (dev->ops->irq_disable)
		dev->ops->irq_disable(dev, port);
}