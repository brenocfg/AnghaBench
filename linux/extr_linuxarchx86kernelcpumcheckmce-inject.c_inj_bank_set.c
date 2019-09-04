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
struct mce {scalar_t__ bank; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  do_inject () ; 
 scalar_t__ n_banks ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__) ; 

__attribute__((used)) static int inj_bank_set(void *data, u64 val)
{
	struct mce *m = (struct mce *)data;

	if (val >= n_banks) {
		pr_err("Non-existent MCE bank: %llu\n", val);
		return -EINVAL;
	}

	m->bank = val;
	do_inject();

	return 0;
}