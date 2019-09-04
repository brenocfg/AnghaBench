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
struct mtrr_iter {int mtrr_disabled; int /*<<< orphan*/  mtrr_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtrr_is_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtrr_lookup_fixed_start (struct mtrr_iter*) ; 
 int /*<<< orphan*/  mtrr_lookup_var_start (struct mtrr_iter*) ; 

__attribute__((used)) static void mtrr_lookup_start(struct mtrr_iter *iter)
{
	if (!mtrr_is_enabled(iter->mtrr_state)) {
		iter->mtrr_disabled = true;
		return;
	}

	if (!mtrr_lookup_fixed_start(iter))
		mtrr_lookup_var_start(iter);
}