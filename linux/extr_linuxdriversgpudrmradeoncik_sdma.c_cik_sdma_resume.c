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
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cik_sdma_enable (struct radeon_device*,int) ; 
 int cik_sdma_gfx_resume (struct radeon_device*) ; 
 int cik_sdma_load_microcode (struct radeon_device*) ; 
 int cik_sdma_rlc_resume (struct radeon_device*) ; 

int cik_sdma_resume(struct radeon_device *rdev)
{
	int r;

	r = cik_sdma_load_microcode(rdev);
	if (r)
		return r;

	/* unhalt the MEs */
	cik_sdma_enable(rdev, true);

	/* start the gfx rings and rlc compute queues */
	r = cik_sdma_gfx_resume(rdev);
	if (r)
		return r;
	r = cik_sdma_rlc_resume(rdev);
	if (r)
		return r;

	return 0;
}