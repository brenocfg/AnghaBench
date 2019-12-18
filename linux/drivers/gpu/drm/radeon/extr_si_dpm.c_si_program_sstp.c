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
 int /*<<< orphan*/  CG_SSP ; 
 int /*<<< orphan*/  R600_SSTU_DFLT ; 
 int /*<<< orphan*/  R600_SST_DFLT ; 
 int SST (int /*<<< orphan*/ ) ; 
 int SSTU (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void si_program_sstp(struct radeon_device *rdev)
{
	WREG32(CG_SSP, (SSTU(R600_SSTU_DFLT) | SST(R600_SST_DFLT)));
}