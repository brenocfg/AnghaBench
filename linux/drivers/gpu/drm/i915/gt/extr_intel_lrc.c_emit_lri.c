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
struct lri {int /*<<< orphan*/  value; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  MI_LOAD_REGISTER_IMM (unsigned int) ; 
 int /*<<< orphan*/  MI_NOOP ; 
 int /*<<< orphan*/  i915_mmio_reg_offset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 *emit_lri(u32 *batch, const struct lri *lri, unsigned int count)
{
	GEM_BUG_ON(!count || count > 63);

	*batch++ = MI_LOAD_REGISTER_IMM(count);
	do {
		*batch++ = i915_mmio_reg_offset(lri->reg);
		*batch++ = lri->value;
	} while (lri++, --count);
	*batch++ = MI_NOOP;

	return batch;
}