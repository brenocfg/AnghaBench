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
struct spi_device {int /*<<< orphan*/  irq; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  state; } ;
struct mcp251x_priv {int force_quit; int /*<<< orphan*/  mcp_lock; TYPE_1__ can; int /*<<< orphan*/  transceiver; int /*<<< orphan*/ * wq; struct spi_device* spi; } ;

/* Variables and functions */
 int /*<<< orphan*/  CANINTE ; 
 int /*<<< orphan*/  CANINTF ; 
 int /*<<< orphan*/  CAN_LED_EVENT_STOP ; 
 int /*<<< orphan*/  CAN_STATE_STOPPED ; 
 int /*<<< orphan*/  TXBCTRL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  can_led_event (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close_candev (struct net_device*) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct mcp251x_priv*) ; 
 int /*<<< orphan*/  mcp251x_clean (struct net_device*) ; 
 int /*<<< orphan*/  mcp251x_hw_sleep (struct spi_device*) ; 
 int /*<<< orphan*/  mcp251x_power_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcp251x_write_reg (struct spi_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct mcp251x_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int mcp251x_stop(struct net_device *net)
{
	struct mcp251x_priv *priv = netdev_priv(net);
	struct spi_device *spi = priv->spi;

	close_candev(net);

	priv->force_quit = 1;
	free_irq(spi->irq, priv);
	destroy_workqueue(priv->wq);
	priv->wq = NULL;

	mutex_lock(&priv->mcp_lock);

	/* Disable and clear pending interrupts */
	mcp251x_write_reg(spi, CANINTE, 0x00);
	mcp251x_write_reg(spi, CANINTF, 0x00);

	mcp251x_write_reg(spi, TXBCTRL(0), 0);
	mcp251x_clean(net);

	mcp251x_hw_sleep(spi);

	mcp251x_power_enable(priv->transceiver, 0);

	priv->can.state = CAN_STATE_STOPPED;

	mutex_unlock(&priv->mcp_lock);

	can_led_event(net, CAN_LED_EVENT_STOP);

	return 0;
}