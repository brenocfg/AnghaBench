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
typedef  int u8 ;
struct amdgpu_device {int dummy; } ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int amdgpu_si_copy_bytes_to_smc (struct amdgpu_device*,int,int const*,int,int) ; 

int amdgpu_si_program_jump_on_start(struct amdgpu_device *adev)
{
	static const u8 data[] = { 0x0E, 0x00, 0x40, 0x40 };

	return amdgpu_si_copy_bytes_to_smc(adev, 0x0, data, 4, sizeof(data)+1);
}