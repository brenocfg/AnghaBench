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
struct TYPE_3__ {int /*<<< orphan*/  ucode_version; } ;
struct sdma_firmware_header_v1_0 {int /*<<< orphan*/  ucode_feature_version; TYPE_1__ header; } ;
struct amdgpu_sdma_instance {int feature_version; int burst_nop; void* fw_version; TYPE_2__* fw; } ;
struct TYPE_4__ {scalar_t__ data; } ;

/* Variables and functions */
 int amdgpu_ucode_validate (TYPE_2__*) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sdma_v4_0_init_inst_ctx(struct amdgpu_sdma_instance *sdma_inst)
{
	int err = 0;
	const struct sdma_firmware_header_v1_0 *hdr;

	err = amdgpu_ucode_validate(sdma_inst->fw);
	if (err)
		return err;

	hdr = (const struct sdma_firmware_header_v1_0 *)sdma_inst->fw->data;
	sdma_inst->fw_version = le32_to_cpu(hdr->header.ucode_version);
	sdma_inst->feature_version = le32_to_cpu(hdr->ucode_feature_version);

	if (sdma_inst->feature_version >= 20)
		sdma_inst->burst_nop = true;

	return 0;
}