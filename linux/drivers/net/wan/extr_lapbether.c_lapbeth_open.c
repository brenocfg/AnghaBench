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
 int ENODEV ; 
 int LAPB_OK ; 
 int lapb_register (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lapbeth_callbacks ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static int lapbeth_open(struct net_device *dev)
{
	int err;

	if ((err = lapb_register(dev, &lapbeth_callbacks)) != LAPB_OK) {
		pr_err("lapb_register error: %d\n", err);
		return -ENODEV;
	}

	netif_start_queue(dev);
	return 0;
}