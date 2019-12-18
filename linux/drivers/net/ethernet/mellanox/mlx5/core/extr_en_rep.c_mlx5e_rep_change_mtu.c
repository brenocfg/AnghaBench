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
 int mlx5e_change_mtu (struct net_device*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mlx5e_rep_change_mtu(struct net_device *netdev, int new_mtu)
{
	return mlx5e_change_mtu(netdev, new_mtu, NULL);
}