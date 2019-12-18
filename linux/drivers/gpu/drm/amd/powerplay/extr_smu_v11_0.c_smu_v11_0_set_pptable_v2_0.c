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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct smu_context {struct amdgpu_device* adev; } ;
struct smc_firmware_header_v2_0 {int /*<<< orphan*/  ppt_size_bytes; int /*<<< orphan*/  ppt_offset_bytes; } ;
struct TYPE_4__ {TYPE_1__* fw; } ;
struct amdgpu_device {TYPE_2__ pm; } ;
struct TYPE_3__ {scalar_t__ data; } ;

/* Variables and functions */
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smu_v11_0_set_pptable_v2_0(struct smu_context *smu, void **table, uint32_t *size)
{
	struct amdgpu_device *adev = smu->adev;
	uint32_t ppt_offset_bytes;
	const struct smc_firmware_header_v2_0 *v2;

	v2 = (const struct smc_firmware_header_v2_0 *) adev->pm.fw->data;

	ppt_offset_bytes = le32_to_cpu(v2->ppt_offset_bytes);
	*size = le32_to_cpu(v2->ppt_size_bytes);
	*table = (uint8_t *)v2 + ppt_offset_bytes;

	return 0;
}