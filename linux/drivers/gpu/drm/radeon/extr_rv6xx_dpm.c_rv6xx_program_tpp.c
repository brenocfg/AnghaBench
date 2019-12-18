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
 int /*<<< orphan*/  R600_TPC_DFLT ; 
 int /*<<< orphan*/  R600_TPU_DFLT ; 
 int /*<<< orphan*/  r600_set_tpc (struct radeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r600_set_tpu (struct radeon_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rv6xx_program_tpp(struct radeon_device *rdev)
{
	r600_set_tpu(rdev, R600_TPU_DFLT);
	r600_set_tpc(rdev, R600_TPC_DFLT);
}