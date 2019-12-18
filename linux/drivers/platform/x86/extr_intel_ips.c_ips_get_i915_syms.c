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
struct ips_driver {void* gpu_turbo_disable; void* gpu_busy; void* gpu_lower; void* gpu_raise; void* read_mch_val; } ;

/* Variables and functions */
 int /*<<< orphan*/  i915_gpu_busy ; 
 int /*<<< orphan*/  i915_gpu_lower ; 
 int /*<<< orphan*/  i915_gpu_raise ; 
 int /*<<< orphan*/  i915_gpu_turbo_disable ; 
 int /*<<< orphan*/  i915_read_mch_val ; 
 void* symbol_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  symbol_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ips_get_i915_syms(struct ips_driver *ips)
{
	ips->read_mch_val = symbol_get(i915_read_mch_val);
	if (!ips->read_mch_val)
		goto out_err;
	ips->gpu_raise = symbol_get(i915_gpu_raise);
	if (!ips->gpu_raise)
		goto out_put_mch;
	ips->gpu_lower = symbol_get(i915_gpu_lower);
	if (!ips->gpu_lower)
		goto out_put_raise;
	ips->gpu_busy = symbol_get(i915_gpu_busy);
	if (!ips->gpu_busy)
		goto out_put_lower;
	ips->gpu_turbo_disable = symbol_get(i915_gpu_turbo_disable);
	if (!ips->gpu_turbo_disable)
		goto out_put_busy;

	return true;

out_put_busy:
	symbol_put(i915_gpu_busy);
out_put_lower:
	symbol_put(i915_gpu_lower);
out_put_raise:
	symbol_put(i915_gpu_raise);
out_put_mch:
	symbol_put(i915_read_mch_val);
out_err:
	return false;
}