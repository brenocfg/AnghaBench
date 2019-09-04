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
typedef  int /*<<< orphan*/  u64 ;
struct i915_address_space {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void nop_clear_range(struct i915_address_space *vm,
			    u64 start, u64 length)
{
}