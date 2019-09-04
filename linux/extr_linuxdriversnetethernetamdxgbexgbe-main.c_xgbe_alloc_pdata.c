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
struct xgbe_prv_data {int /*<<< orphan*/  dev_state; int /*<<< orphan*/  msg_enable; int /*<<< orphan*/  vxlan_ports; int /*<<< orphan*/  mdio_complete; int /*<<< orphan*/  i2c_complete; int /*<<< orphan*/  i2c_mutex; int /*<<< orphan*/  tstamp_lock; int /*<<< orphan*/  rss_mutex; int /*<<< orphan*/  xpcs_lock; int /*<<< orphan*/  lock; struct device* dev; struct net_device* netdev; } ;
struct net_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct xgbe_prv_data* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,struct device*) ; 
 int /*<<< orphan*/  XGBE_DOWN ; 
 int /*<<< orphan*/  XGBE_MAX_DMA_CHANNELS ; 
 int /*<<< orphan*/  XGBE_STOPPED ; 
 struct net_device* alloc_etherdev_mq (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  default_msg_level ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct xgbe_prv_data* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_msg_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct xgbe_prv_data *xgbe_alloc_pdata(struct device *dev)
{
	struct xgbe_prv_data *pdata;
	struct net_device *netdev;

	netdev = alloc_etherdev_mq(sizeof(struct xgbe_prv_data),
				   XGBE_MAX_DMA_CHANNELS);
	if (!netdev) {
		dev_err(dev, "alloc_etherdev_mq failed\n");
		return ERR_PTR(-ENOMEM);
	}
	SET_NETDEV_DEV(netdev, dev);
	pdata = netdev_priv(netdev);
	pdata->netdev = netdev;
	pdata->dev = dev;

	spin_lock_init(&pdata->lock);
	spin_lock_init(&pdata->xpcs_lock);
	mutex_init(&pdata->rss_mutex);
	spin_lock_init(&pdata->tstamp_lock);
	mutex_init(&pdata->i2c_mutex);
	init_completion(&pdata->i2c_complete);
	init_completion(&pdata->mdio_complete);
	INIT_LIST_HEAD(&pdata->vxlan_ports);

	pdata->msg_enable = netif_msg_init(debug, default_msg_level);

	set_bit(XGBE_DOWN, &pdata->dev_state);
	set_bit(XGBE_STOPPED, &pdata->dev_state);

	return pdata;
}