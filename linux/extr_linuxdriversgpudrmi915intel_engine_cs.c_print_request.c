#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  seqno; int /*<<< orphan*/  context; TYPE_2__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  attr; } ;
struct i915_request {scalar_t__ emitted_jiffies; TYPE_3__ fence; int /*<<< orphan*/  global_seqno; TYPE_1__ sched; int /*<<< orphan*/  i915; } ;
struct drm_printer {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_5__ {char* (* get_timeline_name ) (TYPE_3__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  drm_printf (struct drm_printer*,char*,char const*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ i915_request_completed (struct i915_request*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  jiffies_to_msecs (scalar_t__) ; 
 int print_sched_attr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int,int) ; 
 char* stub1 (TYPE_3__*) ; 

__attribute__((used)) static void print_request(struct drm_printer *m,
			  struct i915_request *rq,
			  const char *prefix)
{
	const char *name = rq->fence.ops->get_timeline_name(&rq->fence);
	char buf[80] = "";
	int x = 0;

	x = print_sched_attr(rq->i915, &rq->sched.attr, buf, x, sizeof(buf));

	drm_printf(m, "%s%x%s [%llx:%x]%s @ %dms: %s\n",
		   prefix,
		   rq->global_seqno,
		   i915_request_completed(rq) ? "!" : "",
		   rq->fence.context, rq->fence.seqno,
		   buf,
		   jiffies_to_msecs(jiffies - rq->emitted_jiffies),
		   name);
}