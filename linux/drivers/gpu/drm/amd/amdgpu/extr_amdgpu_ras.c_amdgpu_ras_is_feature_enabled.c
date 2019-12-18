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
struct ras_common_if {int /*<<< orphan*/  block; } ;
struct amdgpu_ras {int features; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 struct amdgpu_ras* amdgpu_ras_get_context (struct amdgpu_device*) ; 

__attribute__((used)) static int amdgpu_ras_is_feature_enabled(struct amdgpu_device *adev,
		struct ras_common_if *head)
{
	struct amdgpu_ras *con = amdgpu_ras_get_context(adev);

	return con->features & BIT(head->block);
}