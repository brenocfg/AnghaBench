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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct smu_context {struct amdgpu_device* adev; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP1 ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmMP1_SMN_C2PMSG_82 ; 
 int /*<<< orphan*/  mmMP1_SMN_C2PMSG_90 ; 
 int /*<<< orphan*/  pr_err (char*,int,int,int /*<<< orphan*/ ) ; 
 int smu_msg_get_index (struct smu_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smu_v12_0_send_msg_without_waiting (struct smu_context*,int /*<<< orphan*/ ) ; 
 int smu_v12_0_wait_for_response (struct smu_context*) ; 

__attribute__((used)) static int
smu_v12_0_send_msg_with_param(struct smu_context *smu, uint16_t msg,
			      uint32_t param)
{
	struct amdgpu_device *adev = smu->adev;
	int ret = 0, index = 0;

	index = smu_msg_get_index(smu, msg);
	if (index < 0)
		return index;

	ret = smu_v12_0_wait_for_response(smu);
	if (ret)
		pr_err("Failed to send message 0x%x, response 0x%x, param 0x%x\n",
		       index, ret, param);

	WREG32_SOC15(MP1, 0, mmMP1_SMN_C2PMSG_90, 0);

	WREG32_SOC15(MP1, 0, mmMP1_SMN_C2PMSG_82, param);

	smu_v12_0_send_msg_without_waiting(smu, (uint16_t)index);

	ret = smu_v12_0_wait_for_response(smu);
	if (ret)
		pr_err("Failed to send message 0x%x, response 0x%x param 0x%x\n",
		       index, ret, param);

	return ret;
}