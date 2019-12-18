#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int /*<<< orphan*/  flags; } ;
struct ctcm_priv {TYPE_1__** channel; scalar_t__ fsm; } ;
struct ccwgroup_device {int /*<<< orphan*/ * cdev; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {struct net_device* netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTCM_DBF_DEV (int /*<<< orphan*/ ,struct net_device*,char*) ; 
 size_t CTCM_READ ; 
 size_t CTCM_WRITE ; 
 int ENODEV ; 
 int /*<<< orphan*/  IFF_RUNNING ; 
 int /*<<< orphan*/  SETUP ; 
 int /*<<< orphan*/  ccw_device_set_offline (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  channel_free (TYPE_1__*) ; 
 int /*<<< orphan*/  channel_remove (TYPE_1__*) ; 
 int /*<<< orphan*/  ctcm_close (struct net_device*) ; 
 int /*<<< orphan*/  ctcm_free_netdevice (struct net_device*) ; 
 struct ctcm_priv* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_fsm (scalar_t__) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static int ctcm_shutdown_device(struct ccwgroup_device *cgdev)
{
	struct ctcm_priv *priv;
	struct net_device *dev;

	priv = dev_get_drvdata(&cgdev->dev);
	if (!priv)
		return -ENODEV;

	if (priv->channel[CTCM_READ]) {
		dev = priv->channel[CTCM_READ]->netdev;
		CTCM_DBF_DEV(SETUP, dev, "");
		/* Close the device */
		ctcm_close(dev);
		dev->flags &= ~IFF_RUNNING;
		channel_free(priv->channel[CTCM_READ]);
	} else
		dev = NULL;

	if (priv->channel[CTCM_WRITE])
		channel_free(priv->channel[CTCM_WRITE]);

	if (dev) {
		unregister_netdev(dev);
		ctcm_free_netdevice(dev);
	}

	if (priv->fsm)
		kfree_fsm(priv->fsm);

	ccw_device_set_offline(cgdev->cdev[1]);
	ccw_device_set_offline(cgdev->cdev[0]);
	channel_remove(priv->channel[CTCM_READ]);
	channel_remove(priv->channel[CTCM_WRITE]);
	priv->channel[CTCM_READ] = priv->channel[CTCM_WRITE] = NULL;

	return 0;

}