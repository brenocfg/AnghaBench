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
typedef  int /*<<< orphan*/  u32 ;
struct i915_request {int dummy; } ;

/* Variables and functions */
 int MI_INVALIDATE_BSD ; 
 int MI_INVALIDATE_TLB ; 
 int gen6_flush_dw (struct i915_request*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int gen6_bsd_ring_flush(struct i915_request *rq, u32 mode)
{
	return gen6_flush_dw(rq, mode, MI_INVALIDATE_TLB | MI_INVALIDATE_BSD);
}