#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_4__ {scalar_t__ beacon; } ;
struct TYPE_3__ {scalar_t__ misc; scalar_t__ retries; scalar_t__ fragment; scalar_t__ code; scalar_t__ nwid; } ;
struct iw_statistics {TYPE_2__ miss; TYPE_1__ discard; } ;
struct ks_wlan_private {scalar_t__ dev_state; struct iw_statistics wstats; } ;

/* Variables and functions */
 scalar_t__ DEVICE_STATE_READY ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 struct ks_wlan_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  update_phyinfo ; 

__attribute__((used)) static struct iw_statistics *ks_get_wireless_stats(struct net_device *dev)
{
	struct ks_wlan_private *priv = netdev_priv(dev);
	struct iw_statistics *wstats = &priv->wstats;

	if (!atomic_read(&update_phyinfo))
		return (priv->dev_state < DEVICE_STATE_READY) ? NULL : wstats;

	/*
	 * Packets discarded in the wireless adapter due to wireless
	 * specific problems
	 */
	wstats->discard.nwid = 0;	/* Rx invalid nwid      */
	wstats->discard.code = 0;	/* Rx invalid crypt     */
	wstats->discard.fragment = 0;	/* Rx invalid frag      */
	wstats->discard.retries = 0;	/* Tx excessive retries */
	wstats->discard.misc = 0;	/* Invalid misc         */
	wstats->miss.beacon = 0;	/* Missed beacon        */

	return wstats;
}