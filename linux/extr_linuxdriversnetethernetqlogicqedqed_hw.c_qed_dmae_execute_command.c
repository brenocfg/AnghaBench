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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u64 ;
typedef  int u32 ;
typedef  int u16 ;
struct qed_ptt {int dummy; } ;
struct TYPE_2__ {struct dmae_cmd* p_dmae_cmd; int /*<<< orphan*/  completion_word_phys_addr; } ;
struct qed_hwfn {TYPE_1__ dmae_info; } ;
struct qed_dmae_params {int flags; } ;
struct dmae_cmd {void* comp_val; void* comp_addr_hi; void* comp_addr_lo; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMAE_COMPLETION_VAL ; 
 int DMAE_MAX_RW_SIZE ; 
 int /*<<< orphan*/  DP_NOTICE (struct qed_hwfn*,char*,int,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  QED_DMAE_ADDRESS_GRC ; 
 int QED_DMAE_FLAG_RW_REPL_SRC ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int qed_dmae_execute_sub_operation (struct qed_hwfn*,struct qed_ptt*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qed_dmae_opcode (struct qed_hwfn*,int,int,struct qed_dmae_params*) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qed_dmae_execute_command(struct qed_hwfn *p_hwfn,
				    struct qed_ptt *p_ptt,
				    u64 src_addr, u64 dst_addr,
				    u8 src_type, u8 dst_type,
				    u32 size_in_dwords,
				    struct qed_dmae_params *p_params)
{
	dma_addr_t phys = p_hwfn->dmae_info.completion_word_phys_addr;
	u16 length_cur = 0, i = 0, cnt_split = 0, length_mod = 0;
	struct dmae_cmd *cmd = p_hwfn->dmae_info.p_dmae_cmd;
	u64 src_addr_split = 0, dst_addr_split = 0;
	u16 length_limit = DMAE_MAX_RW_SIZE;
	int qed_status = 0;
	u32 offset = 0;

	qed_dmae_opcode(p_hwfn,
			(src_type == QED_DMAE_ADDRESS_GRC),
			(dst_type == QED_DMAE_ADDRESS_GRC),
			p_params);

	cmd->comp_addr_lo = cpu_to_le32(lower_32_bits(phys));
	cmd->comp_addr_hi = cpu_to_le32(upper_32_bits(phys));
	cmd->comp_val = cpu_to_le32(DMAE_COMPLETION_VAL);

	/* Check if the grc_addr is valid like < MAX_GRC_OFFSET */
	cnt_split = size_in_dwords / length_limit;
	length_mod = size_in_dwords % length_limit;

	src_addr_split = src_addr;
	dst_addr_split = dst_addr;

	for (i = 0; i <= cnt_split; i++) {
		offset = length_limit * i;

		if (!(p_params->flags & QED_DMAE_FLAG_RW_REPL_SRC)) {
			if (src_type == QED_DMAE_ADDRESS_GRC)
				src_addr_split = src_addr + offset;
			else
				src_addr_split = src_addr + (offset * 4);
		}

		if (dst_type == QED_DMAE_ADDRESS_GRC)
			dst_addr_split = dst_addr + offset;
		else
			dst_addr_split = dst_addr + (offset * 4);

		length_cur = (cnt_split == i) ? length_mod : length_limit;

		/* might be zero on last iteration */
		if (!length_cur)
			continue;

		qed_status = qed_dmae_execute_sub_operation(p_hwfn,
							    p_ptt,
							    src_addr_split,
							    dst_addr_split,
							    src_type,
							    dst_type,
							    length_cur);
		if (qed_status) {
			DP_NOTICE(p_hwfn,
				  "qed_dmae_execute_sub_operation Failed with error 0x%x. source_addr 0x%llx, destination addr 0x%llx, size_in_dwords 0x%x\n",
				  qed_status, src_addr, dst_addr, length_cur);
			break;
		}
	}

	return qed_status;
}