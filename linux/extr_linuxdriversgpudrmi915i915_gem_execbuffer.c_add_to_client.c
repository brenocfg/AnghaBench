#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct i915_request {TYPE_2__* file_priv; int /*<<< orphan*/  client_link; } ;
struct drm_file {TYPE_2__* driver_priv; } ;
struct TYPE_3__ {int /*<<< orphan*/  request_list; } ;
struct TYPE_4__ {TYPE_1__ mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
add_to_client(struct i915_request *rq, struct drm_file *file)
{
	rq->file_priv = file->driver_priv;
	list_add_tail(&rq->client_link, &rq->file_priv->mm.request_list);
}