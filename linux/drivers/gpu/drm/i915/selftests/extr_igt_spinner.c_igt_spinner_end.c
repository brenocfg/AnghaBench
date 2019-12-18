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
struct igt_spinner {int /*<<< orphan*/  gt; int /*<<< orphan*/ * batch; } ;

/* Variables and functions */
 int /*<<< orphan*/  MI_BATCH_BUFFER_END ; 
 int /*<<< orphan*/  intel_gt_chipset_flush (int /*<<< orphan*/ ) ; 

void igt_spinner_end(struct igt_spinner *spin)
{
	*spin->batch = MI_BATCH_BUFFER_END;
	intel_gt_chipset_flush(spin->gt);
}