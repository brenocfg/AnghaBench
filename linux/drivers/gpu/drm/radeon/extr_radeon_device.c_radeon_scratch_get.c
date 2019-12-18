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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int num_reg; int* free; int /*<<< orphan*/ * reg; } ;
struct radeon_device {TYPE_1__ scratch; } ;

/* Variables and functions */
 int EINVAL ; 

int radeon_scratch_get(struct radeon_device *rdev, uint32_t *reg)
{
	int i;

	for (i = 0; i < rdev->scratch.num_reg; i++) {
		if (rdev->scratch.free[i]) {
			rdev->scratch.free[i] = false;
			*reg = rdev->scratch.reg[i];
			return 0;
		}
	}
	return -EINVAL;
}