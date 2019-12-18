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
struct i915_wa {int val; int read; int /*<<< orphan*/  mask; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,char const*,char const*,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_mmio_reg_offset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
wa_verify(const struct i915_wa *wa, u32 cur, const char *name, const char *from)
{
	if ((cur ^ wa->val) & wa->read) {
		DRM_ERROR("%s workaround lost on %s! (%x=%x/%x, expected %x, mask=%x)\n",
			  name, from, i915_mmio_reg_offset(wa->reg),
			  cur, cur & wa->read,
			  wa->val, wa->mask);

		return false;
	}

	return true;
}