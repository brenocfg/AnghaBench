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
struct ras_common_if {int block; int const type; int /*<<< orphan*/  name; int /*<<< orphan*/  sub_block_index; } ;
struct amdgpu_ras {int features; } ;
struct amdgpu_device {int dummy; } ;
typedef  enum amdgpu_ras_error_type { ____Placeholder_amdgpu_ras_error_type } amdgpu_ras_error_type ;

/* Variables and functions */
 int AMDGPU_RAS_BLOCK_COUNT ; 
 int AMDGPU_RAS_ERROR__NONE ; 
 scalar_t__ __amdgpu_ras_feature_enable (struct amdgpu_device*,struct ras_common_if*,int) ; 
 scalar_t__ amdgpu_ras_feature_enable (struct amdgpu_device*,struct ras_common_if*,int) ; 
 struct amdgpu_ras* amdgpu_ras_get_context (struct amdgpu_device*) ; 
 int /*<<< orphan*/  ras_block_str (int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int amdgpu_ras_enable_all_features(struct amdgpu_device *adev,
		bool bypass)
{
	struct amdgpu_ras *con = amdgpu_ras_get_context(adev);
	int ras_block_count = AMDGPU_RAS_BLOCK_COUNT;
	int i;
	const enum amdgpu_ras_error_type default_ras_type =
		AMDGPU_RAS_ERROR__NONE;

	for (i = 0; i < ras_block_count; i++) {
		struct ras_common_if head = {
			.block = i,
			.type = default_ras_type,
			.sub_block_index = 0,
		};
		strcpy(head.name, ras_block_str(i));
		if (bypass) {
			/*
			 * bypass psp. vbios enable ras for us.
			 * so just create the obj
			 */
			if (__amdgpu_ras_feature_enable(adev, &head, 1))
				break;
		} else {
			if (amdgpu_ras_feature_enable(adev, &head, 1))
				break;
		}
	}

	return con->features;
}