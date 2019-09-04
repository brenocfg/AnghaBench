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
 int /*<<< orphan*/  __nfp_repr_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_priv (struct net_device*) ; 

void nfp_repr_free(struct net_device *netdev)
{
	__nfp_repr_free(netdev_priv(netdev));
}