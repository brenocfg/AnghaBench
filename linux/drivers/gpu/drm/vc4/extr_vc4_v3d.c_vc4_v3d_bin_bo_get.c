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
struct vc4_dev {int /*<<< orphan*/  bin_bo_lock; int /*<<< orphan*/  bin_bo_kref; scalar_t__ bin_bo; } ;

/* Variables and functions */
 int bin_bo_alloc (struct vc4_dev*) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int vc4_v3d_bin_bo_get(struct vc4_dev *vc4, bool *used)
{
	int ret = 0;

	mutex_lock(&vc4->bin_bo_lock);

	if (used && *used)
		goto complete;

	if (vc4->bin_bo)
		kref_get(&vc4->bin_bo_kref);
	else
		ret = bin_bo_alloc(vc4);

	if (ret == 0 && used)
		*used = true;

complete:
	mutex_unlock(&vc4->bin_bo_lock);

	return ret;
}