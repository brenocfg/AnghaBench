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
struct rt_stats {int dummy; } ;
struct r8192_priv {int /*<<< orphan*/  irq; int /*<<< orphan*/  gpio_polling_timer; int /*<<< orphan*/  watch_dog_timer; TYPE_1__* ops; int /*<<< orphan*/  stats; } ;
struct net_device {int /*<<< orphan*/  irq; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* init_adapter_variable ) (struct net_device*) ;int /*<<< orphan*/  (* get_eeprom_size ) (struct net_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_INIT ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _rtl92e_get_channel_map (struct net_device*) ; 
 int /*<<< orphan*/  _rtl92e_init_priv_constant (struct net_device*) ; 
 int /*<<< orphan*/  _rtl92e_init_priv_handler (struct net_device*) ; 
 int /*<<< orphan*/  _rtl92e_init_priv_lock (struct r8192_priv*) ; 
 int /*<<< orphan*/  _rtl92e_init_priv_task (struct net_device*) ; 
 int /*<<< orphan*/  _rtl92e_init_priv_variable (struct net_device*) ; 
 int /*<<< orphan*/  _rtl92e_irq ; 
 scalar_t__ _rtl92e_pci_initdescring (struct net_device*) ; 
 int /*<<< orphan*/  _rtl92e_watchdog_timer_cb ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,...) ; 
 scalar_t__ request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  rtl92e_check_rfctrl_gpio_timer ; 
 int /*<<< orphan*/  rtl92e_dm_init (struct net_device*) ; 
 int /*<<< orphan*/  rtl92e_irq_disable (struct net_device*) ; 
 struct r8192_priv* rtllib_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct net_device*) ; 
 int /*<<< orphan*/  stub2 (struct net_device*) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static short _rtl92e_init(struct net_device *dev)
{
	struct r8192_priv *priv = rtllib_priv(dev);

	memset(&priv->stats, 0, sizeof(struct rt_stats));

	_rtl92e_init_priv_handler(dev);
	_rtl92e_init_priv_constant(dev);
	_rtl92e_init_priv_variable(dev);
	_rtl92e_init_priv_lock(priv);
	_rtl92e_init_priv_task(dev);
	priv->ops->get_eeprom_size(dev);
	priv->ops->init_adapter_variable(dev);
	_rtl92e_get_channel_map(dev);

	rtl92e_dm_init(dev);

	timer_setup(&priv->watch_dog_timer, _rtl92e_watchdog_timer_cb, 0);

	timer_setup(&priv->gpio_polling_timer, rtl92e_check_rfctrl_gpio_timer,
		    0);

	rtl92e_irq_disable(dev);
	if (request_irq(dev->irq, _rtl92e_irq, IRQF_SHARED, dev->name, dev)) {
		netdev_err(dev, "Error allocating IRQ %d", dev->irq);
		return -1;
	}

	priv->irq = dev->irq;
	RT_TRACE(COMP_INIT, "IRQ %d\n", dev->irq);

	if (_rtl92e_pci_initdescring(dev) != 0) {
		netdev_err(dev, "Endopoints initialization failed");
		free_irq(dev->irq, dev);
		return -1;
	}

	return 0;
}