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
struct neigh_parms {int /*<<< orphan*/  neigh_setup; struct net_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  bond_neigh_init ; 

__attribute__((used)) static int bond_neigh_setup(struct net_device *dev,
			    struct neigh_parms *parms)
{
	/* modify only our neigh_parms */
	if (parms->dev == dev)
		parms->neigh_setup = bond_neigh_init;

	return 0;
}