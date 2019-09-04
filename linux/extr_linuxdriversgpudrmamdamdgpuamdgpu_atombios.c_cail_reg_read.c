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
struct card_info {TYPE_1__* dev; } ;
struct amdgpu_device {int dummy; } ;
struct TYPE_2__ {struct amdgpu_device* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t cail_reg_read(struct card_info *info, uint32_t reg)
{
	struct amdgpu_device *adev = info->dev->dev_private;
	uint32_t r;

	r = RREG32(reg);
	return r;
}