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
struct be_set_eqd {int dummy; } ;
struct be_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __be_cmd_modify_eqd (struct be_adapter*,struct be_set_eqd*,int) ; 
 int min (int,int) ; 

int be_cmd_modify_eqd(struct be_adapter *adapter, struct be_set_eqd *set_eqd,
		      int num)
{
	int num_eqs, i = 0;

	while (num) {
		num_eqs = min(num, 8);
		__be_cmd_modify_eqd(adapter, &set_eqd[i], num_eqs);
		i += num_eqs;
		num -= num_eqs;
	}

	return 0;
}