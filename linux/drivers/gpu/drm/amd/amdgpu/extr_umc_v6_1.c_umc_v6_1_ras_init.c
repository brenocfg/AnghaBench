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
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_umc_for_each_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umc_v6_1_ras_init_per_channel ; 

__attribute__((used)) static void umc_v6_1_ras_init(struct amdgpu_device *adev)
{
	void *ras_error_status = NULL;

	amdgpu_umc_for_each_channel(umc_v6_1_ras_init_per_channel);
}