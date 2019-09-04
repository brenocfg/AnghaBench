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
struct TYPE_2__ {int ctrlmode_supported; int /*<<< orphan*/  do_get_berr_counter; int /*<<< orphan*/  do_set_mode; int /*<<< orphan*/  do_set_bittiming; int /*<<< orphan*/ * bittiming_const; } ;
struct sja1000_priv {void* priv; int /*<<< orphan*/  cmdreg_lock; TYPE_1__ can; struct net_device* dev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int CAN_CTRLMODE_3_SAMPLES ; 
 int CAN_CTRLMODE_BERR_REPORTING ; 
 int CAN_CTRLMODE_LISTENONLY ; 
 int CAN_CTRLMODE_LOOPBACK ; 
 int CAN_CTRLMODE_ONE_SHOT ; 
 int CAN_CTRLMODE_PRESUME_ACK ; 
 int /*<<< orphan*/  SJA1000_ECHO_SKB_MAX ; 
 struct net_device* alloc_candev (int,int /*<<< orphan*/ ) ; 
 struct sja1000_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  sja1000_bittiming_const ; 
 int /*<<< orphan*/  sja1000_get_berr_counter ; 
 int /*<<< orphan*/  sja1000_set_bittiming ; 
 int /*<<< orphan*/  sja1000_set_mode ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct net_device *alloc_sja1000dev(int sizeof_priv)
{
	struct net_device *dev;
	struct sja1000_priv *priv;

	dev = alloc_candev(sizeof(struct sja1000_priv) + sizeof_priv,
		SJA1000_ECHO_SKB_MAX);
	if (!dev)
		return NULL;

	priv = netdev_priv(dev);

	priv->dev = dev;
	priv->can.bittiming_const = &sja1000_bittiming_const;
	priv->can.do_set_bittiming = sja1000_set_bittiming;
	priv->can.do_set_mode = sja1000_set_mode;
	priv->can.do_get_berr_counter = sja1000_get_berr_counter;
	priv->can.ctrlmode_supported = CAN_CTRLMODE_LOOPBACK |
				       CAN_CTRLMODE_LISTENONLY |
				       CAN_CTRLMODE_3_SAMPLES |
				       CAN_CTRLMODE_ONE_SHOT |
				       CAN_CTRLMODE_BERR_REPORTING |
				       CAN_CTRLMODE_PRESUME_ACK;

	spin_lock_init(&priv->cmdreg_lock);

	if (sizeof_priv)
		priv->priv = (void *)priv + sizeof(struct sja1000_priv);

	return dev;
}