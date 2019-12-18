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
struct TYPE_2__ {int /*<<< orphan*/  vma; } ;
struct intel_engine_cs {TYPE_1__ wa_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  i915_vma_unpin_and_release (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lrc_destroy_wa_ctx(struct intel_engine_cs *engine)
{
	i915_vma_unpin_and_release(&engine->wa_ctx.vma, 0);
}