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
struct bonding {int dummy; } ;
struct bond_option {int (* set ) (struct bonding*,struct bond_opt_value const*) ;} ;
struct bond_opt_value {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int EINVAL ; 
 int ENOENT ; 
 scalar_t__ WARN_ON (int) ; 
 int bond_opt_check_deps (struct bonding*,struct bond_option const*) ; 
 int /*<<< orphan*/  bond_opt_error_interpret (struct bonding*,struct bond_option const*,int,struct bond_opt_value*) ; 
 struct bond_option* bond_opt_get (unsigned int) ; 
 struct bond_opt_value* bond_opt_parse (struct bond_option const*,struct bond_opt_value*) ; 
 int stub1 (struct bonding*,struct bond_opt_value const*) ; 

int __bond_opt_set(struct bonding *bond,
		   unsigned int option, struct bond_opt_value *val)
{
	const struct bond_opt_value *retval = NULL;
	const struct bond_option *opt;
	int ret = -ENOENT;

	ASSERT_RTNL();

	opt = bond_opt_get(option);
	if (WARN_ON(!val) || WARN_ON(!opt))
		goto out;
	ret = bond_opt_check_deps(bond, opt);
	if (ret)
		goto out;
	retval = bond_opt_parse(opt, val);
	if (!retval) {
		ret = -EINVAL;
		goto out;
	}
	ret = opt->set(bond, retval);
out:
	if (ret)
		bond_opt_error_interpret(bond, opt, ret, val);

	return ret;
}