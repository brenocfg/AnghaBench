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
typedef  scalar_t__ u64 ;
struct bond_option {int dummy; } ;
struct bond_opt_value {scalar_t__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  BOND_VALFLAG_MAX ; 
 int /*<<< orphan*/  BOND_VALFLAG_MIN ; 
 struct bond_opt_value* bond_opt_get_flags (struct bond_option const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool bond_opt_check_range(const struct bond_option *opt, u64 val)
{
	const struct bond_opt_value *minval, *maxval;

	minval = bond_opt_get_flags(opt, BOND_VALFLAG_MIN);
	maxval = bond_opt_get_flags(opt, BOND_VALFLAG_MAX);
	if (!maxval || (minval && val < minval->value) || val > maxval->value)
		return false;

	return true;
}