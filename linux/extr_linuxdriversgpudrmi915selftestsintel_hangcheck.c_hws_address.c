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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {scalar_t__ start; } ;
struct i915_vma {TYPE_1__ node; } ;
struct TYPE_4__ {int context; } ;
struct i915_request {TYPE_2__ fence; } ;

/* Variables and functions */
 scalar_t__ offset_in_page (int) ; 

__attribute__((used)) static u64 hws_address(const struct i915_vma *hws,
		       const struct i915_request *rq)
{
	return hws->node.start + offset_in_page(sizeof(u32)*rq->fence.context);
}