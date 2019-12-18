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
struct net_device {int dummy; } ;
struct TYPE_3__ {scalar_t__ expires; } ;
struct mace_data {int timeout_active; TYPE_1__ tx_timeout; } ;

/* Variables and functions */
 scalar_t__ TX_TIMEOUT ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  del_timer (TYPE_1__*) ; 
 scalar_t__ jiffies ; 
 struct mace_data* netdev_priv (struct net_device*) ; 

__attribute__((used)) static inline void mace_set_timeout(struct net_device *dev)
{
    struct mace_data *mp = netdev_priv(dev);

    if (mp->timeout_active)
	del_timer(&mp->tx_timeout);
    mp->tx_timeout.expires = jiffies + TX_TIMEOUT;
    add_timer(&mp->tx_timeout);
    mp->timeout_active = 1;
}