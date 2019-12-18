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
struct wilc_vif {struct wilc* wilc; } ;
struct wilc {int /*<<< orphan*/  sync_event; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int ETIME ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 struct wilc_vif* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int wilc_wlan_start (struct wilc*) ; 

__attribute__((used)) static int wilc_start_firmware(struct net_device *dev)
{
	struct wilc_vif *vif = netdev_priv(dev);
	struct wilc *wilc = vif->wilc;
	int ret = 0;

	ret = wilc_wlan_start(wilc);
	if (ret < 0)
		return ret;

	if (!wait_for_completion_timeout(&wilc->sync_event,
					 msecs_to_jiffies(5000)))
		return -ETIME;

	return 0;
}