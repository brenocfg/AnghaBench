#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct smu_context {struct amdgpu_device* adev; } ;
struct TYPE_6__ {int /*<<< orphan*/  ucode_array_offset_bytes; } ;
struct smc_firmware_header_v1_0 {TYPE_3__ header; } ;
struct TYPE_5__ {TYPE_1__* fw; } ;
struct amdgpu_device {int usec_timeout; TYPE_2__ pm; } ;
struct TYPE_4__ {scalar_t__ data; } ;

/* Variables and functions */
 int ETIME ; 
 int MP1_FIRMWARE_FLAGS__INTERRUPTS_ENABLED_MASK ; 
 int MP1_FIRMWARE_FLAGS__INTERRUPTS_ENABLED__SHIFT ; 
 int MP1_Public ; 
 int MP1_SMC_SIZE ; 
 int MP1_SMN_PUB_CTRL__RESET_MASK ; 
 int MP1_SRAM ; 
 int RREG32_PCIE (int) ; 
 int /*<<< orphan*/  WREG32_PCIE (int,int const) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int smnMP1_FIRMWARE_FLAGS ; 
 int smnMP1_PUB_CTRL ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int smu_v11_0_load_microcode(struct smu_context *smu)
{
	struct amdgpu_device *adev = smu->adev;
	const uint32_t *src;
	const struct smc_firmware_header_v1_0 *hdr;
	uint32_t addr_start = MP1_SRAM;
	uint32_t i;
	uint32_t mp1_fw_flags;

	hdr = (const struct smc_firmware_header_v1_0 *) adev->pm.fw->data;
	src = (const uint32_t *)(adev->pm.fw->data +
		le32_to_cpu(hdr->header.ucode_array_offset_bytes));

	for (i = 1; i < MP1_SMC_SIZE/4 - 1; i++) {
		WREG32_PCIE(addr_start, src[i]);
		addr_start += 4;
	}

	WREG32_PCIE(MP1_Public | (smnMP1_PUB_CTRL & 0xffffffff),
		1 & MP1_SMN_PUB_CTRL__RESET_MASK);
	WREG32_PCIE(MP1_Public | (smnMP1_PUB_CTRL & 0xffffffff),
		1 & ~MP1_SMN_PUB_CTRL__RESET_MASK);

	for (i = 0; i < adev->usec_timeout; i++) {
		mp1_fw_flags = RREG32_PCIE(MP1_Public |
			(smnMP1_FIRMWARE_FLAGS & 0xffffffff));
		if ((mp1_fw_flags & MP1_FIRMWARE_FLAGS__INTERRUPTS_ENABLED_MASK) >>
			MP1_FIRMWARE_FLAGS__INTERRUPTS_ENABLED__SHIFT)
			break;
		udelay(1);
	}

	if (i == adev->usec_timeout)
		return -ETIME;

	return 0;
}