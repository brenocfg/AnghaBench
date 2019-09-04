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
struct can_berr_counter {int dummy; } ;
struct peak_canfd_priv {struct can_berr_counter bec; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct peak_canfd_priv* netdev_priv (struct net_device const*) ; 

__attribute__((used)) static int peak_canfd_get_berr_counter(const struct net_device *ndev,
				       struct can_berr_counter *bec)
{
	struct peak_canfd_priv *priv = netdev_priv(ndev);

	*bec = priv->bec;
	return 0;
}