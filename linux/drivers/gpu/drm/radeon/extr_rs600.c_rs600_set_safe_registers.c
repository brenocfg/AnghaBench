#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  reg_safe_bm_size; int /*<<< orphan*/  reg_safe_bm; } ;
struct TYPE_4__ {TYPE_1__ r300; } ;
struct radeon_device {TYPE_2__ config; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rs600_reg_safe_bm ; 

void rs600_set_safe_registers(struct radeon_device *rdev)
{
	rdev->config.r300.reg_safe_bm = rs600_reg_safe_bm;
	rdev->config.r300.reg_safe_bm_size = ARRAY_SIZE(rs600_reg_safe_bm);
}