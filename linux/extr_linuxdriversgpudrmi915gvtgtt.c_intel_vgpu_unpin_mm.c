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
struct intel_vgpu_mm {int /*<<< orphan*/  pincount; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec_if_positive (int /*<<< orphan*/ *) ; 

void intel_vgpu_unpin_mm(struct intel_vgpu_mm *mm)
{
	atomic_dec_if_positive(&mm->pincount);
}