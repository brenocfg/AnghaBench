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
typedef  int u32 ;
struct TYPE_2__ {int num_wb; int /*<<< orphan*/  used; } ;
struct amdgpu_device {TYPE_1__ wb; } ;

/* Variables and functions */
 int /*<<< orphan*/  __clear_bit (int,int /*<<< orphan*/ ) ; 

void amdgpu_device_wb_free(struct amdgpu_device *adev, u32 wb)
{
	wb >>= 3;
	if (wb < adev->wb.num_wb)
		__clear_bit(wb, adev->wb.used);
}