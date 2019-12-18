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
struct vc4_dev {int /*<<< orphan*/  bin_bo_lock; int /*<<< orphan*/  bin_bo_kref; } ;

/* Variables and functions */
 int /*<<< orphan*/  bin_bo_release ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void vc4_v3d_bin_bo_put(struct vc4_dev *vc4)
{
	mutex_lock(&vc4->bin_bo_lock);
	kref_put(&vc4->bin_bo_kref, bin_bo_release);
	mutex_unlock(&vc4->bin_bo_lock);
}