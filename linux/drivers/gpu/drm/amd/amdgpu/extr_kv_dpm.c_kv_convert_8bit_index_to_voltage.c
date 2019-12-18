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
typedef  int u16 ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static u16 kv_convert_8bit_index_to_voltage(struct amdgpu_device *adev,
					    u16 voltage)
{
	return 6200 - (voltage * 25);
}