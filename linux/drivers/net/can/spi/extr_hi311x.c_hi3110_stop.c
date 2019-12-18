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
struct hi3110_priv {int force_quit; int /*<<< orphan*/  hi3110_lock; TYPE_1__ can; int /*<<< orphan*/  transceiver; int /*<<< orphan*/ * wq; struct spi_device* spi; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_LED_EVENT_STOP ; 
 int /*<<< orphan*/  CAN_STATE_STOPPED ; 
 int /*<<< orphan*/  HI3110_READ_INTF ; 
 int /*<<< orphan*/  HI3110_WRITE_CTRL1 ; 
 int /*<<< orphan*/  HI3110_WRITE_INTE ; 
 int /*<<< orphan*/  can_led_event (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close_candev (struct net_device*) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct hi3110_priv*) ; 
 int /*<<< orphan*/  hi3110_clean (struct net_device*) ; 
 int /*<<< orphan*/  hi3110_hw_sleep (struct spi_device*) ; 
 int /*<<< orphan*/  hi3110_power_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hi3110_read (struct spi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hi3110_write (struct spi_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct hi3110_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int hi3110_stop(struct net_device *net)
{
	struct hi3110_priv *priv = netdev_priv(net);
	struct spi_device *spi = priv->spi;

	close_candev(net);

	priv->force_quit = 1;
	free_irq(spi->irq, priv);
	destroy_workqueue(priv->wq);
	priv->wq = NULL;

	mutex_lock(&priv->hi3110_lock);

	/* Disable transmit, interrupts and clear flags */
	hi3110_write(spi, HI3110_WRITE_CTRL1, 0x0);
	hi3110_write(spi, HI3110_WRITE_INTE, 0x0);
	hi3110_read(spi, HI3110_READ_INTF);

	hi3110_clean(net);

	hi3110_hw_sleep(spi);

	hi3110_power_enable(priv->transceiver, 0);

	priv->can.state = CAN_STATE_STOPPED;

	mutex_unlock(&priv->hi3110_lock);

	can_led_event(net, CAN_LED_EVENT_STOP);

	return 0;
}