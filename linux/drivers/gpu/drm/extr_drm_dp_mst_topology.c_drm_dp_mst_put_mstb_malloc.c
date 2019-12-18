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
struct drm_dp_mst_branch {int /*<<< orphan*/  malloc_kref; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,struct drm_dp_mst_branch*,scalar_t__) ; 
 int /*<<< orphan*/  drm_dp_free_mst_branch_device ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ kref_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
drm_dp_mst_put_mstb_malloc(struct drm_dp_mst_branch *mstb)
{
	DRM_DEBUG("mstb %p (%d)\n", mstb, kref_read(&mstb->malloc_kref) - 1);
	kref_put(&mstb->malloc_kref, drm_dp_free_mst_branch_device);
}