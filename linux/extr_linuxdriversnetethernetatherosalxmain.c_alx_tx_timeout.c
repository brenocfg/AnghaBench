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
struct alx_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  alx_schedule_reset (struct alx_priv*) ; 
 struct alx_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void alx_tx_timeout(struct net_device *dev)
{
	struct alx_priv *alx = netdev_priv(dev);

	alx_schedule_reset(alx);
}