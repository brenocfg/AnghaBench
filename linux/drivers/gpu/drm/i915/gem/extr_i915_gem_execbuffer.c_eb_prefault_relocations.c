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
struct i915_execbuffer {unsigned int buffer_count; int /*<<< orphan*/ * exec; } ;
struct TYPE_2__ {int /*<<< orphan*/  prefault_disable; } ;

/* Variables and functions */
 int check_relocations (int /*<<< orphan*/ *) ; 
 TYPE_1__ i915_modparams ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int eb_prefault_relocations(const struct i915_execbuffer *eb)
{
	const unsigned int count = eb->buffer_count;
	unsigned int i;

	if (unlikely(i915_modparams.prefault_disable))
		return 0;

	for (i = 0; i < count; i++) {
		int err;

		err = check_relocations(&eb->exec[i]);
		if (err)
			return err;
	}

	return 0;
}