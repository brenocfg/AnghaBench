#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct gfx_firmware_header_v1_0 {int /*<<< orphan*/  jt_size; int /*<<< orphan*/  jt_offset; } ;
struct common_firmware_header {int /*<<< orphan*/  ucode_array_offset_bytes; int /*<<< orphan*/  ucode_size_bytes; } ;
struct amdgpu_firmware_info {TYPE_1__* fw; int /*<<< orphan*/ * kaddr; } ;
struct TYPE_2__ {scalar_t__ data; } ;

/* Variables and functions */
 int ALIGN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int amdgpu_ucode_patch_jt(struct amdgpu_firmware_info *ucode,
				uint64_t mc_addr, void *kptr)
{
	const struct gfx_firmware_header_v1_0 *header = NULL;
	const struct common_firmware_header *comm_hdr = NULL;
	uint8_t* src_addr = NULL;
	uint8_t* dst_addr = NULL;

	if (NULL == ucode->fw)
		return 0;

	comm_hdr = (const struct common_firmware_header *)ucode->fw->data;
	header = (const struct gfx_firmware_header_v1_0 *)ucode->fw->data;
	dst_addr = ucode->kaddr +
			   ALIGN(le32_to_cpu(comm_hdr->ucode_size_bytes),
			   PAGE_SIZE);
	src_addr = (uint8_t *)ucode->fw->data +
			   le32_to_cpu(comm_hdr->ucode_array_offset_bytes) +
			   (le32_to_cpu(header->jt_offset) * 4);
	memcpy(dst_addr, src_addr, le32_to_cpu(header->jt_size) * 4);

	return 0;
}