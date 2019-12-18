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
struct rvt_mr {int /*<<< orphan*/  mr; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct rvt_mr*) ; 
 int /*<<< orphan*/  rvt_deinit_mregion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rvt_free_lkey (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __rvt_free_mr(struct rvt_mr *mr)
{
	rvt_free_lkey(&mr->mr);
	rvt_deinit_mregion(&mr->mr);
	kfree(mr);
}