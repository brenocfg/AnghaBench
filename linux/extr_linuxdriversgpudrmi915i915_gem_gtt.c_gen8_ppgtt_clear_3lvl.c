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
typedef  int /*<<< orphan*/  u64 ;
struct i915_address_space {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pdp; } ;

/* Variables and functions */
 int /*<<< orphan*/  gen8_ppgtt_clear_pdp (struct i915_address_space*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* i915_vm_to_ppgtt (struct i915_address_space*) ; 

__attribute__((used)) static void gen8_ppgtt_clear_3lvl(struct i915_address_space *vm,
				  u64 start, u64 length)
{
	gen8_ppgtt_clear_pdp(vm, &i915_vm_to_ppgtt(vm)->pdp, start, length);
}