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
struct radeon_device {TYPE_1__* vce_fw; } ;
struct TYPE_2__ {scalar_t__ size; } ;

/* Variables and functions */
 scalar_t__ VCE_V1_0_DATA_SIZE ; 
 scalar_t__ VCE_V1_0_FW_SIZE ; 
 scalar_t__ VCE_V1_0_STACK_SIZE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 

unsigned vce_v1_0_bo_size(struct radeon_device *rdev)
{
	WARN_ON(VCE_V1_0_FW_SIZE < rdev->vce_fw->size);
	return VCE_V1_0_FW_SIZE + VCE_V1_0_STACK_SIZE + VCE_V1_0_DATA_SIZE;
}