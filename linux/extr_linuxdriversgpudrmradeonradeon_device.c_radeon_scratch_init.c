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
struct TYPE_2__ {int num_reg; int* free; scalar_t__ reg_base; scalar_t__* reg; } ;
struct radeon_device {scalar_t__ family; TYPE_1__ scratch; } ;

/* Variables and functions */
 scalar_t__ CHIP_R300 ; 
 scalar_t__ RADEON_SCRATCH_REG0 ; 

void radeon_scratch_init(struct radeon_device *rdev)
{
	int i;

	/* FIXME: check this out */
	if (rdev->family < CHIP_R300) {
		rdev->scratch.num_reg = 5;
	} else {
		rdev->scratch.num_reg = 7;
	}
	rdev->scratch.reg_base = RADEON_SCRATCH_REG0;
	for (i = 0; i < rdev->scratch.num_reg; i++) {
		rdev->scratch.free[i] = true;
		rdev->scratch.reg[i] = rdev->scratch.reg_base + (i * 4);
	}
}