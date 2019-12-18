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
struct bond_params {int /*<<< orphan*/  mode; } ;
struct bonding {int /*<<< orphan*/  dev; struct bond_params params; } ;
struct bond_option {int /*<<< orphan*/  name; int /*<<< orphan*/  unsuppmodes; } ;
struct bond_opt_value {int /*<<< orphan*/  value; int /*<<< orphan*/  string; } ;

/* Variables and functions */
 int /*<<< orphan*/  BOND_OPT_MODE ; 
 struct bond_opt_value* bond_opt_get_val (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bond_opt_dep_print(struct bonding *bond,
			       const struct bond_option *opt)
{
	const struct bond_opt_value *modeval;
	struct bond_params *params;

	params = &bond->params;
	modeval = bond_opt_get_val(BOND_OPT_MODE, params->mode);
	if (test_bit(params->mode, &opt->unsuppmodes))
		netdev_err(bond->dev, "option %s: mode dependency failed, not supported in mode %s(%llu)\n",
			   opt->name, modeval->string, modeval->value);
}