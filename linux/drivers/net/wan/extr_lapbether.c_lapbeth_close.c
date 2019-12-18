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
struct net_device {int dummy; } ;

/* Variables and functions */
 int LAPB_OK ; 
 int lapb_unregister (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static int lapbeth_close(struct net_device *dev)
{
	int err;

	netif_stop_queue(dev);

	if ((err = lapb_unregister(dev)) != LAPB_OK)
		pr_err("lapb_unregister error: %d\n", err);

	return 0;
}