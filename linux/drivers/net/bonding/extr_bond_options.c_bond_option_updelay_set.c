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
struct TYPE_2__ {int /*<<< orphan*/  updelay; } ;
struct bonding {TYPE_1__ params; } ;
struct bond_opt_value {int dummy; } ;

/* Variables and functions */
 int _bond_option_delay_set (struct bonding*,struct bond_opt_value const*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bond_option_updelay_set(struct bonding *bond,
				   const struct bond_opt_value *newval)
{
	return _bond_option_delay_set(bond, newval, "up delay",
				      &bond->params.updelay);
}