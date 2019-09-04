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
typedef  int u32 ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int RREG32 (int /*<<< orphan*/ ) ; 
 int SMC_CLK_EN ; 
 int /*<<< orphan*/  SMC_IO ; 
 int SMC_RST_N ; 

bool rv770_is_smc_running(struct radeon_device *rdev)
{
	u32 tmp;

	tmp = RREG32(SMC_IO);

	if ((tmp & SMC_RST_N) && (tmp & SMC_CLK_EN))
		return true;
	else
		return false;
}