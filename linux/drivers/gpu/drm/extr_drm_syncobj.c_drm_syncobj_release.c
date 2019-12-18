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
struct drm_file {int /*<<< orphan*/  syncobj_idr; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_syncobj_release_handle ; 
 int /*<<< orphan*/  idr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_for_each (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct drm_file*) ; 

void
drm_syncobj_release(struct drm_file *file_private)
{
	idr_for_each(&file_private->syncobj_idr,
		     &drm_syncobj_release_handle, file_private);
	idr_destroy(&file_private->syncobj_idr);
}