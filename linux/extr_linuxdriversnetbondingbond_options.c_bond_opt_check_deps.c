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
struct bond_params {int /*<<< orphan*/  mode; } ;
struct bonding {TYPE_1__* dev; struct bond_params params; } ;
struct bond_option {int flags; int /*<<< orphan*/  unsuppmodes; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int BOND_OPTFLAG_IFDOWN ; 
 int BOND_OPTFLAG_NOSLAVES ; 
 int EACCES ; 
 int EBUSY ; 
 int ENOTEMPTY ; 
 int IFF_UP ; 
 scalar_t__ bond_has_slaves (struct bonding*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bond_opt_check_deps(struct bonding *bond,
			       const struct bond_option *opt)
{
	struct bond_params *params = &bond->params;

	if (test_bit(params->mode, &opt->unsuppmodes))
		return -EACCES;
	if ((opt->flags & BOND_OPTFLAG_NOSLAVES) && bond_has_slaves(bond))
		return -ENOTEMPTY;
	if ((opt->flags & BOND_OPTFLAG_IFDOWN) && (bond->dev->flags & IFF_UP))
		return -EBUSY;

	return 0;
}