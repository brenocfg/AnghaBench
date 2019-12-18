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
struct i915_syncmap {int /*<<< orphan*/  bitmap; } ;

/* Variables and functions */
 scalar_t__ BITS_PER_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  BUILD_BUG_ON_NOT_POWER_OF_2 (scalar_t__) ; 
 scalar_t__ KSYNCMAP ; 
 scalar_t__ SHIFT ; 

void i915_syncmap_init(struct i915_syncmap **root)
{
	BUILD_BUG_ON_NOT_POWER_OF_2(KSYNCMAP);
	BUILD_BUG_ON_NOT_POWER_OF_2(SHIFT);
	BUILD_BUG_ON(KSYNCMAP > BITS_PER_TYPE((*root)->bitmap));
	*root = NULL;
}