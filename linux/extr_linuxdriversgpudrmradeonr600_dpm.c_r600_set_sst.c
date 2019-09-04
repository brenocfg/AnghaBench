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
typedef  int /*<<< orphan*/  u32 ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_SSP ; 
 int /*<<< orphan*/  CG_SST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CG_SST_MASK ; 
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void r600_set_sst(struct radeon_device *rdev, u32 t)
{
	WREG32_P(CG_SSP, CG_SST(t), ~CG_SST_MASK);
}