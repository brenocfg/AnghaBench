#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_8__ {int* cp_table_ptr; } ;
struct radeon_device {scalar_t__ family; TYPE_7__* mec_fw; TYPE_6__* me_fw; TYPE_5__* pfp_fw; TYPE_4__* ce_fw; TYPE_2__* mec2_fw; scalar_t__ new_fw; TYPE_1__ rlc; } ;
struct TYPE_10__ {int /*<<< orphan*/  const ucode_array_offset_bytes; } ;
struct gfx_firmware_header_v1_0 {int /*<<< orphan*/  const jt_size; int /*<<< orphan*/  const jt_offset; TYPE_3__ header; } ;
typedef  int /*<<< orphan*/  __le32 ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_14__ {int data; } ;
struct TYPE_13__ {int data; } ;
struct TYPE_12__ {int data; } ;
struct TYPE_11__ {int data; } ;
struct TYPE_9__ {int data; } ;

/* Variables and functions */
 scalar_t__ CHIP_KAVERI ; 
 int CP_MEC_TABLE_OFFSET ; 
 int CP_ME_TABLE_OFFSET ; 
 int CP_ME_TABLE_SIZE ; 
 int be32_to_cpu (int /*<<< orphan*/  const) ; 
 int cpu_to_le32 (int) ; 
 int le32_to_cpu (int /*<<< orphan*/  const) ; 

void cik_init_cp_pg_table(struct radeon_device *rdev)
{
	volatile u32 *dst_ptr;
	int me, i, max_me = 4;
	u32 bo_offset = 0;
	u32 table_offset, table_size;

	if (rdev->family == CHIP_KAVERI)
		max_me = 5;

	if (rdev->rlc.cp_table_ptr == NULL)
		return;

	/* write the cp table buffer */
	dst_ptr = rdev->rlc.cp_table_ptr;
	for (me = 0; me < max_me; me++) {
		if (rdev->new_fw) {
			const __le32 *fw_data;
			const struct gfx_firmware_header_v1_0 *hdr;

			if (me == 0) {
				hdr = (const struct gfx_firmware_header_v1_0 *)rdev->ce_fw->data;
				fw_data = (const __le32 *)
					(rdev->ce_fw->data + le32_to_cpu(hdr->header.ucode_array_offset_bytes));
				table_offset = le32_to_cpu(hdr->jt_offset);
				table_size = le32_to_cpu(hdr->jt_size);
			} else if (me == 1) {
				hdr = (const struct gfx_firmware_header_v1_0 *)rdev->pfp_fw->data;
				fw_data = (const __le32 *)
					(rdev->pfp_fw->data + le32_to_cpu(hdr->header.ucode_array_offset_bytes));
				table_offset = le32_to_cpu(hdr->jt_offset);
				table_size = le32_to_cpu(hdr->jt_size);
			} else if (me == 2) {
				hdr = (const struct gfx_firmware_header_v1_0 *)rdev->me_fw->data;
				fw_data = (const __le32 *)
					(rdev->me_fw->data + le32_to_cpu(hdr->header.ucode_array_offset_bytes));
				table_offset = le32_to_cpu(hdr->jt_offset);
				table_size = le32_to_cpu(hdr->jt_size);
			} else if (me == 3) {
				hdr = (const struct gfx_firmware_header_v1_0 *)rdev->mec_fw->data;
				fw_data = (const __le32 *)
					(rdev->mec_fw->data + le32_to_cpu(hdr->header.ucode_array_offset_bytes));
				table_offset = le32_to_cpu(hdr->jt_offset);
				table_size = le32_to_cpu(hdr->jt_size);
			} else {
				hdr = (const struct gfx_firmware_header_v1_0 *)rdev->mec2_fw->data;
				fw_data = (const __le32 *)
					(rdev->mec2_fw->data + le32_to_cpu(hdr->header.ucode_array_offset_bytes));
				table_offset = le32_to_cpu(hdr->jt_offset);
				table_size = le32_to_cpu(hdr->jt_size);
			}

			for (i = 0; i < table_size; i ++) {
				dst_ptr[bo_offset + i] =
					cpu_to_le32(le32_to_cpu(fw_data[table_offset + i]));
			}
			bo_offset += table_size;
		} else {
			const __be32 *fw_data;
			table_size = CP_ME_TABLE_SIZE;

			if (me == 0) {
				fw_data = (const __be32 *)rdev->ce_fw->data;
				table_offset = CP_ME_TABLE_OFFSET;
			} else if (me == 1) {
				fw_data = (const __be32 *)rdev->pfp_fw->data;
				table_offset = CP_ME_TABLE_OFFSET;
			} else if (me == 2) {
				fw_data = (const __be32 *)rdev->me_fw->data;
				table_offset = CP_ME_TABLE_OFFSET;
			} else {
				fw_data = (const __be32 *)rdev->mec_fw->data;
				table_offset = CP_MEC_TABLE_OFFSET;
			}

			for (i = 0; i < table_size; i ++) {
				dst_ptr[bo_offset + i] =
					cpu_to_le32(be32_to_cpu(fw_data[table_offset + i]));
			}
			bo_offset += table_size;
		}
	}
}