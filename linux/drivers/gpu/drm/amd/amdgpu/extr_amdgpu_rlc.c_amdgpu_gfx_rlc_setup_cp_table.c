#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_18__ {int /*<<< orphan*/  const ucode_array_offset_bytes; } ;
struct gfx_firmware_header_v1_0 {int /*<<< orphan*/  const jt_size; int /*<<< orphan*/  const jt_offset; TYPE_9__ header; } ;
struct TYPE_11__ {int* cp_table_ptr; TYPE_1__* funcs; } ;
struct TYPE_17__ {TYPE_7__* mec2_fw; TYPE_6__* mec_fw; TYPE_5__* me_fw; TYPE_4__* pfp_fw; TYPE_3__* ce_fw; TYPE_2__ rlc; } ;
struct amdgpu_device {TYPE_8__ gfx; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_16__ {int data; } ;
struct TYPE_15__ {int data; } ;
struct TYPE_14__ {int data; } ;
struct TYPE_13__ {int data; } ;
struct TYPE_12__ {int data; } ;
struct TYPE_10__ {int (* get_cp_table_num ) (struct amdgpu_device*) ;} ;

/* Variables and functions */
 int cpu_to_le32 (int) ; 
 int le32_to_cpu (int /*<<< orphan*/  const) ; 
 int stub1 (struct amdgpu_device*) ; 

void amdgpu_gfx_rlc_setup_cp_table(struct amdgpu_device *adev)
{
	const __le32 *fw_data;
	volatile u32 *dst_ptr;
	int me, i, max_me;
	u32 bo_offset = 0;
	u32 table_offset, table_size;

	max_me = adev->gfx.rlc.funcs->get_cp_table_num(adev);

	/* write the cp table buffer */
	dst_ptr = adev->gfx.rlc.cp_table_ptr;
	for (me = 0; me < max_me; me++) {
		if (me == 0) {
			const struct gfx_firmware_header_v1_0 *hdr =
				(const struct gfx_firmware_header_v1_0 *)adev->gfx.ce_fw->data;
			fw_data = (const __le32 *)
				(adev->gfx.ce_fw->data +
				 le32_to_cpu(hdr->header.ucode_array_offset_bytes));
			table_offset = le32_to_cpu(hdr->jt_offset);
			table_size = le32_to_cpu(hdr->jt_size);
		} else if (me == 1) {
			const struct gfx_firmware_header_v1_0 *hdr =
				(const struct gfx_firmware_header_v1_0 *)adev->gfx.pfp_fw->data;
			fw_data = (const __le32 *)
				(adev->gfx.pfp_fw->data +
				 le32_to_cpu(hdr->header.ucode_array_offset_bytes));
			table_offset = le32_to_cpu(hdr->jt_offset);
			table_size = le32_to_cpu(hdr->jt_size);
		} else if (me == 2) {
			const struct gfx_firmware_header_v1_0 *hdr =
				(const struct gfx_firmware_header_v1_0 *)adev->gfx.me_fw->data;
			fw_data = (const __le32 *)
				(adev->gfx.me_fw->data +
				 le32_to_cpu(hdr->header.ucode_array_offset_bytes));
			table_offset = le32_to_cpu(hdr->jt_offset);
			table_size = le32_to_cpu(hdr->jt_size);
		} else if (me == 3) {
			const struct gfx_firmware_header_v1_0 *hdr =
				(const struct gfx_firmware_header_v1_0 *)adev->gfx.mec_fw->data;
			fw_data = (const __le32 *)
				(adev->gfx.mec_fw->data +
				 le32_to_cpu(hdr->header.ucode_array_offset_bytes));
			table_offset = le32_to_cpu(hdr->jt_offset);
			table_size = le32_to_cpu(hdr->jt_size);
		} else  if (me == 4) {
			const struct gfx_firmware_header_v1_0 *hdr =
				(const struct gfx_firmware_header_v1_0 *)adev->gfx.mec2_fw->data;
			fw_data = (const __le32 *)
				(adev->gfx.mec2_fw->data +
				 le32_to_cpu(hdr->header.ucode_array_offset_bytes));
			table_offset = le32_to_cpu(hdr->jt_offset);
			table_size = le32_to_cpu(hdr->jt_size);
		}

		for (i = 0; i < table_size; i ++) {
			dst_ptr[bo_offset + i] =
				cpu_to_le32(le32_to_cpu(fw_data[table_offset + i]));
		}

		bo_offset += table_size;
	}
}