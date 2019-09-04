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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct kgd_dev {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void set_scratch_backing_va(struct kgd_dev *kgd,
					uint64_t va, uint32_t vmid)
{
	/* No longer needed on GFXv9. The scratch base address is
	 * passed to the shader by the CP. It's the user mode driver's
	 * responsibility.
	 */
}