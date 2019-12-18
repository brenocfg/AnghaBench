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
struct i915_execbuffer {unsigned int buffer_count; TYPE_1__* args; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int I915_EXEC_BATCH_FIRST ; 

__attribute__((used)) static unsigned int eb_batch_index(const struct i915_execbuffer *eb)
{
	if (eb->args->flags & I915_EXEC_BATCH_FIRST)
		return 0;
	else
		return eb->buffer_count - 1;
}