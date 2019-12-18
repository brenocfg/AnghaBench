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
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct r8192_priv {int /*<<< orphan*/  wx_mutex; int /*<<< orphan*/  reset_wq; } ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int r8192_set_mac_adr(struct net_device *dev, void *mac)
{
	struct r8192_priv *priv = ieee80211_priv(dev);
	struct sockaddr *addr = mac;

	mutex_lock(&priv->wx_mutex);

	ether_addr_copy(dev->dev_addr, addr->sa_data);

	schedule_work(&priv->reset_wq);
	mutex_unlock(&priv->wx_mutex);

	return 0;
}