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
typedef  int u8 ;
typedef  scalar_t__ u64 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct qed_ptt {int dummy; } ;
struct TYPE_2__ {void* p_intermediate_buffer; struct dmae_cmd* p_dmae_cmd; scalar_t__ intermediate_buffer_phys_addr; } ;
struct qed_hwfn {TYPE_1__ dmae_info; } ;
struct dmae_cmd {int /*<<< orphan*/  length_dw; void* dst_addr_lo; void* dst_addr_hi; void* src_addr_lo; void* src_addr_hi; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct qed_hwfn*,char*,scalar_t__,scalar_t__,int) ; 
 int EINVAL ; 
#define  QED_DMAE_ADDRESS_GRC 130 
#define  QED_DMAE_ADDRESS_HOST_PHYS 129 
#define  QED_DMAE_ADDRESS_HOST_VIRT 128 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lower_32_bits (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 int qed_dmae_operation_wait (struct qed_hwfn*) ; 
 int /*<<< orphan*/  qed_dmae_post_command (struct qed_hwfn*,struct qed_ptt*) ; 
 int /*<<< orphan*/  upper_32_bits (scalar_t__) ; 

__attribute__((used)) static int qed_dmae_execute_sub_operation(struct qed_hwfn *p_hwfn,
					  struct qed_ptt *p_ptt,
					  u64 src_addr,
					  u64 dst_addr,
					  u8 src_type,
					  u8 dst_type,
					  u32 length_dw)
{
	dma_addr_t phys = p_hwfn->dmae_info.intermediate_buffer_phys_addr;
	struct dmae_cmd *cmd = p_hwfn->dmae_info.p_dmae_cmd;
	int qed_status = 0;

	switch (src_type) {
	case QED_DMAE_ADDRESS_GRC:
	case QED_DMAE_ADDRESS_HOST_PHYS:
		cmd->src_addr_hi = cpu_to_le32(upper_32_bits(src_addr));
		cmd->src_addr_lo = cpu_to_le32(lower_32_bits(src_addr));
		break;
	/* for virtual source addresses we use the intermediate buffer. */
	case QED_DMAE_ADDRESS_HOST_VIRT:
		cmd->src_addr_hi = cpu_to_le32(upper_32_bits(phys));
		cmd->src_addr_lo = cpu_to_le32(lower_32_bits(phys));
		memcpy(&p_hwfn->dmae_info.p_intermediate_buffer[0],
		       (void *)(uintptr_t)src_addr,
		       length_dw * sizeof(u32));
		break;
	default:
		return -EINVAL;
	}

	switch (dst_type) {
	case QED_DMAE_ADDRESS_GRC:
	case QED_DMAE_ADDRESS_HOST_PHYS:
		cmd->dst_addr_hi = cpu_to_le32(upper_32_bits(dst_addr));
		cmd->dst_addr_lo = cpu_to_le32(lower_32_bits(dst_addr));
		break;
	/* for virtual source addresses we use the intermediate buffer. */
	case QED_DMAE_ADDRESS_HOST_VIRT:
		cmd->dst_addr_hi = cpu_to_le32(upper_32_bits(phys));
		cmd->dst_addr_lo = cpu_to_le32(lower_32_bits(phys));
		break;
	default:
		return -EINVAL;
	}

	cmd->length_dw = cpu_to_le16((u16)length_dw);

	qed_dmae_post_command(p_hwfn, p_ptt);

	qed_status = qed_dmae_operation_wait(p_hwfn);

	if (qed_status) {
		DP_NOTICE(p_hwfn,
			  "qed_dmae_host2grc: Wait Failed. source_addr 0x%llx, grc_addr 0x%llx, size_in_dwords 0x%x\n",
			  src_addr, dst_addr, length_dw);
		return qed_status;
	}

	if (dst_type == QED_DMAE_ADDRESS_HOST_VIRT)
		memcpy((void *)(uintptr_t)(dst_addr),
		       &p_hwfn->dmae_info.p_intermediate_buffer[0],
		       length_dw * sizeof(u32));

	return 0;
}