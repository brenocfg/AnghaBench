#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct i915_request {int /*<<< orphan*/  client_link; struct drm_i915_file_private* file_priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  request_list; } ;
struct drm_i915_file_private {TYPE_1__ mm; } ;
struct drm_file {struct drm_i915_file_private* driver_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
add_to_client(struct i915_request *rq, struct drm_file *file)
{
	struct drm_i915_file_private *file_priv = file->driver_priv;

	rq->file_priv = file_priv;

	spin_lock(&file_priv->mm.lock);
	list_add_tail(&rq->client_link, &file_priv->mm.request_list);
	spin_unlock(&file_priv->mm.lock);
}