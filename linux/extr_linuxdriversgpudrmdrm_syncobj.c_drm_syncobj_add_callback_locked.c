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
struct drm_syncobj_cb {int /*<<< orphan*/  node; int /*<<< orphan*/  func; } ;
struct drm_syncobj {int /*<<< orphan*/  cb_list; } ;
typedef  int /*<<< orphan*/  drm_syncobj_func_t ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void drm_syncobj_add_callback_locked(struct drm_syncobj *syncobj,
					    struct drm_syncobj_cb *cb,
					    drm_syncobj_func_t func)
{
	cb->func = func;
	list_add_tail(&cb->node, &syncobj->cb_list);
}