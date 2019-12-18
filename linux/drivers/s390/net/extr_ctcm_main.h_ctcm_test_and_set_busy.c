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
struct net_device {scalar_t__ ml_priv; } ;
struct ctcm_priv {int /*<<< orphan*/  tbusy; } ;

/* Variables and functions */
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int ctcm_test_and_set_busy(struct net_device *dev)
{
	netif_stop_queue(dev);
	return test_and_set_bit(0,
			&(((struct ctcm_priv *)dev->ml_priv)->tbusy));
}