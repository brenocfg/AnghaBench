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
struct intel_engine_cs {size_t uabi_class; } ;
struct i915_gpu_error {int /*<<< orphan*/ * reset_engine_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline u32 i915_reset_engine_count(struct i915_gpu_error *error,
					  struct intel_engine_cs *engine)
{
	return atomic_read(&error->reset_engine_count[engine->uabi_class]);
}