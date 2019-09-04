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
typedef  int /*<<< orphan*/  u32 ;
struct i915_request {TYPE_2__* engine; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* signal ) (struct i915_request*,int /*<<< orphan*/ *) ;} ;
struct TYPE_4__ {TYPE_1__ semaphore; } ;

/* Variables and functions */
 void i9xx_emit_breadcrumb (struct i915_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct i915_request*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gen6_sema_emit_breadcrumb(struct i915_request *rq, u32 *cs)
{
	return i9xx_emit_breadcrumb(rq, rq->engine->semaphore.signal(rq, cs));
}