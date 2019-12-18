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
struct enc28j60_net {int /*<<< orphan*/  lock; TYPE_1__* spi; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECON1 ; 
 int /*<<< orphan*/  ECON1_RXEN ; 
 int /*<<< orphan*/  ECON1_TXRTS ; 
 int /*<<< orphan*/  ECON2 ; 
 int /*<<< orphan*/  ECON2_PWRSV ; 
 int /*<<< orphan*/  ESTAT ; 
 int /*<<< orphan*/  ESTAT_CLKRDY ; 
 int /*<<< orphan*/  ESTAT_RXBUSY ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ netif_msg_drv (struct enc28j60_net*) ; 
 int /*<<< orphan*/  nolock_reg_bfclr (struct enc28j60_net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nolock_reg_bfset (struct enc28j60_net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  poll_ready (struct enc28j60_net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void enc28j60_lowpower(struct enc28j60_net *priv, bool is_low)
{
	struct device *dev = &priv->spi->dev;

	if (netif_msg_drv(priv))
		dev_dbg(dev, "%s power...\n", is_low ? "low" : "high");

	mutex_lock(&priv->lock);
	if (is_low) {
		nolock_reg_bfclr(priv, ECON1, ECON1_RXEN);
		poll_ready(priv, ESTAT, ESTAT_RXBUSY, 0);
		poll_ready(priv, ECON1, ECON1_TXRTS, 0);
		/* ECON2_VRPS was set during initialization */
		nolock_reg_bfset(priv, ECON2, ECON2_PWRSV);
	} else {
		nolock_reg_bfclr(priv, ECON2, ECON2_PWRSV);
		poll_ready(priv, ESTAT, ESTAT_CLKRDY, ESTAT_CLKRDY);
		/* caller sets ECON1_RXEN */
	}
	mutex_unlock(&priv->lock);
}