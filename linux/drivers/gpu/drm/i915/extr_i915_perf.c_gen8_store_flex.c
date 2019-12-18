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
typedef  int u32 ;
struct intel_context {int /*<<< orphan*/  state; } ;
struct i915_request {int dummy; } ;
struct flex {int offset; int /*<<< orphan*/  value; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int*) ; 
 int LRC_STATE_PN ; 
 int MI_STORE_DWORD_IMM_GEN4 ; 
 int MI_USE_GGTT ; 
 int PAGE_SIZE ; 
 int PTR_ERR (int*) ; 
 int i915_ggtt_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_ring_advance (struct i915_request*,int*) ; 
 int* intel_ring_begin (struct i915_request*,int) ; 

__attribute__((used)) static int
gen8_store_flex(struct i915_request *rq,
		struct intel_context *ce,
		const struct flex *flex, unsigned int count)
{
	u32 offset;
	u32 *cs;

	cs = intel_ring_begin(rq, 4 * count);
	if (IS_ERR(cs))
		return PTR_ERR(cs);

	offset = i915_ggtt_offset(ce->state) + LRC_STATE_PN * PAGE_SIZE;
	do {
		*cs++ = MI_STORE_DWORD_IMM_GEN4 | MI_USE_GGTT;
		*cs++ = offset + (flex->offset + 1) * sizeof(u32);
		*cs++ = 0;
		*cs++ = flex->value;
	} while (flex++, --count);

	intel_ring_advance(rq, cs);

	return 0;
}