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
typedef  int /*<<< orphan*/  u8 ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmBIOS_SCRATCH_4 ; 

__attribute__((used)) static u8 ci_get_memory_module_index(struct amdgpu_device *adev)
{
	return (u8) ((RREG32(mmBIOS_SCRATCH_4) >> 16) & 0xff);
}