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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct cpsw_priv {int /*<<< orphan*/  msg_enable; } ;

/* Variables and functions */
 struct cpsw_priv* netdev_priv (struct net_device*) ; 

void cpsw_set_msglevel(struct net_device *ndev, u32 value)
{
	struct cpsw_priv *priv = netdev_priv(ndev);

	priv->msg_enable = value;
}