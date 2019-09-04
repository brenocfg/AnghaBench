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
 int /*<<< orphan*/  R600_SSTU_DFLT ; 
 int /*<<< orphan*/  R600_SST_DFLT ; 
 int /*<<< orphan*/  r600_set_sst (struct radeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r600_set_sstu (struct radeon_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rv6xx_program_sstp(struct radeon_device *rdev)
{
	r600_set_sstu(rdev, R600_SSTU_DFLT);
	r600_set_sst(rdev, R600_SST_DFLT);
}