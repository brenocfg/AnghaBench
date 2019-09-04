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
struct whitelist {scalar_t__ count; int /*<<< orphan*/ * reg; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;

/* Variables and functions */
 scalar_t__ GEM_WARN_ON (int) ; 
 scalar_t__ RING_MAX_NONPRIV_SLOTS ; 

__attribute__((used)) static void whitelist_reg(struct whitelist *w, i915_reg_t reg)
{
	if (GEM_WARN_ON(w->count >= RING_MAX_NONPRIV_SLOTS))
		return;

	w->reg[w->count++] = reg;
}