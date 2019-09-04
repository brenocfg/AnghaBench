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
struct drm_syncobj_cb {int dummy; } ;
struct drm_syncobj {int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  drm_syncobj_func_t ;

/* Variables and functions */
 int /*<<< orphan*/  drm_syncobj_add_callback_locked (struct drm_syncobj*,struct drm_syncobj_cb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void drm_syncobj_add_callback(struct drm_syncobj *syncobj,
			      struct drm_syncobj_cb *cb,
			      drm_syncobj_func_t func)
{
	spin_lock(&syncobj->lock);
	drm_syncobj_add_callback_locked(syncobj, cb, func);
	spin_unlock(&syncobj->lock);
}