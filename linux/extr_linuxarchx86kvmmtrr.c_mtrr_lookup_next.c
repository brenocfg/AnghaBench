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
struct mtrr_iter {scalar_t__ fixed; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtrr_lookup_fixed_next (struct mtrr_iter*) ; 
 int /*<<< orphan*/  mtrr_lookup_var_next (struct mtrr_iter*) ; 

__attribute__((used)) static void mtrr_lookup_next(struct mtrr_iter *iter)
{
	if (iter->fixed)
		mtrr_lookup_fixed_next(iter);
	else
		mtrr_lookup_var_next(iter);
}