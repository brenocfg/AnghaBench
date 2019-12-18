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
struct rvt_mregion {int mapsz; int /*<<< orphan*/  refcount; int /*<<< orphan*/ * map; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  percpu_ref_exit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rvt_deinit_mregion(struct rvt_mregion *mr)
{
	int i = mr->mapsz;

	mr->mapsz = 0;
	while (i)
		kfree(mr->map[--i]);
	percpu_ref_exit(&mr->refcount);
}