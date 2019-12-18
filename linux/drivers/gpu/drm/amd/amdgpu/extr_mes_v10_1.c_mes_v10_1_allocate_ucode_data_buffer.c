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
struct mes_firmware_header_v1_0 {int /*<<< orphan*/  mes_ucode_data_size_bytes; int /*<<< orphan*/  mes_ucode_data_offset_bytes; } ;
struct TYPE_4__ {int /*<<< orphan*/  data_fw_obj; int /*<<< orphan*/  data_fw_ptr; int /*<<< orphan*/  data_fw_gpu_addr; TYPE_1__* fw; } ;
struct amdgpu_device {TYPE_2__ mes; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_3__ {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_GEM_DOMAIN_GTT ; 
 int amdgpu_bo_create_reserved (struct amdgpu_device*,unsigned int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  amdgpu_bo_kunmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_bo_unreserve (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static int mes_v10_1_allocate_ucode_data_buffer(struct amdgpu_device *adev)
{
	int r;
	const struct mes_firmware_header_v1_0 *mes_hdr;
	const __le32 *fw_data;
	unsigned fw_size;

	mes_hdr = (const struct mes_firmware_header_v1_0 *)
		adev->mes.fw->data;

	fw_data = (const __le32 *)(adev->mes.fw->data +
		   le32_to_cpu(mes_hdr->mes_ucode_data_offset_bytes));
	fw_size = le32_to_cpu(mes_hdr->mes_ucode_data_size_bytes);

	r = amdgpu_bo_create_reserved(adev, fw_size,
				      64 * 1024, AMDGPU_GEM_DOMAIN_GTT,
				      &adev->mes.data_fw_obj,
				      &adev->mes.data_fw_gpu_addr,
				      (void **)&adev->mes.data_fw_ptr);
	if (r) {
		dev_err(adev->dev, "(%d) failed to create mes data fw bo\n", r);
		return r;
	}

	memcpy(adev->mes.data_fw_ptr, fw_data, fw_size);

	amdgpu_bo_kunmap(adev->mes.data_fw_obj);
	amdgpu_bo_unreserve(adev->mes.data_fw_obj);

	return 0;
}