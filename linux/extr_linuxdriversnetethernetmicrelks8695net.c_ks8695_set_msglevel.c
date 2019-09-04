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
struct ks8695_priv {int /*<<< orphan*/  msg_enable; } ;

/* Variables and functions */
 struct ks8695_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void
ks8695_set_msglevel(struct net_device *ndev, u32 value)
{
	struct ks8695_priv *ksp = netdev_priv(ndev);

	ksp->msg_enable = value;
}