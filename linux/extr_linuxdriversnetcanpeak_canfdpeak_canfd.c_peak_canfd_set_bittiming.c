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
struct TYPE_2__ {int /*<<< orphan*/  bittiming; } ;
struct peak_canfd_priv {TYPE_1__ can; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct peak_canfd_priv* netdev_priv (struct net_device*) ; 
 int pucan_set_timing_slow (struct peak_canfd_priv*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int peak_canfd_set_bittiming(struct net_device *ndev)
{
	struct peak_canfd_priv *priv = netdev_priv(ndev);

	return pucan_set_timing_slow(priv, &priv->can.bittiming);
}