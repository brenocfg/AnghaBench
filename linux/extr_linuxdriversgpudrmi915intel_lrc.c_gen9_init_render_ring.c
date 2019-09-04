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
struct intel_engine_cs {int dummy; } ;

/* Variables and functions */
 int gen8_init_common_ring (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  intel_whitelist_workarounds_apply (struct intel_engine_cs*) ; 

__attribute__((used)) static int gen9_init_render_ring(struct intel_engine_cs *engine)
{
	int ret;

	ret = gen8_init_common_ring(engine);
	if (ret)
		return ret;

	intel_whitelist_workarounds_apply(engine);

	return 0;
}