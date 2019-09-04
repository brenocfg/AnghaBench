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
typedef  int u8 ;
struct phy_device {int dummy; } ;
struct dsa_switch {struct b53_device* priv; } ;
struct b53_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B53_CTRL_PAGE ; 
 int /*<<< orphan*/  B53_PORT_CTRL (int) ; 
 int PORT_CTRL_RX_DISABLE ; 
 int PORT_CTRL_TX_DISABLE ; 
 int /*<<< orphan*/  b53_read8 (struct b53_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  b53_write8 (struct b53_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void b53_disable_port(struct dsa_switch *ds, int port, struct phy_device *phy)
{
	struct b53_device *dev = ds->priv;
	u8 reg;

	/* Disable Tx/Rx for the port */
	b53_read8(dev, B53_CTRL_PAGE, B53_PORT_CTRL(port), &reg);
	reg |= PORT_CTRL_RX_DISABLE | PORT_CTRL_TX_DISABLE;
	b53_write8(dev, B53_CTRL_PAGE, B53_PORT_CTRL(port), reg);
}