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
typedef  int u32 ;
typedef  int u16 ;
struct qed_sb_attn_info {int known_attn; struct atten_status_block* sb_attn; } ;
struct qed_hwfn {struct qed_sb_attn_info* p_sb_attn; } ;
struct atten_status_block {scalar_t__ sb_index; int /*<<< orphan*/  atten_ack; int /*<<< orphan*/  atten_bits; } ;
typedef  scalar_t__ __le16 ;

/* Variables and functions */
 int ATTN_STATE_BITS ; 
 int /*<<< orphan*/  DP_INFO (struct qed_hwfn*,char*,...) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  NETIF_MSG_INTR ; 
 int /*<<< orphan*/  dma_rmb () ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int qed_int_assertion (struct qed_hwfn*,int) ; 
 int qed_int_deassertion (struct qed_hwfn*,int) ; 

__attribute__((used)) static int qed_int_attentions(struct qed_hwfn *p_hwfn)
{
	struct qed_sb_attn_info *p_sb_attn_sw = p_hwfn->p_sb_attn;
	struct atten_status_block *p_sb_attn = p_sb_attn_sw->sb_attn;
	u32 attn_bits = 0, attn_acks = 0;
	u16 asserted_bits, deasserted_bits;
	__le16 index;
	int rc = 0;

	/* Read current attention bits/acks - safeguard against attentions
	 * by guaranting work on a synchronized timeframe
	 */
	do {
		index = p_sb_attn->sb_index;
		/* finish reading index before the loop condition */
		dma_rmb();
		attn_bits = le32_to_cpu(p_sb_attn->atten_bits);
		attn_acks = le32_to_cpu(p_sb_attn->atten_ack);
	} while (index != p_sb_attn->sb_index);
	p_sb_attn->sb_index = index;

	/* Attention / Deassertion are meaningful (and in correct state)
	 * only when they differ and consistent with known state - deassertion
	 * when previous attention & current ack, and assertion when current
	 * attention with no previous attention
	 */
	asserted_bits = (attn_bits & ~attn_acks & ATTN_STATE_BITS) &
		~p_sb_attn_sw->known_attn;
	deasserted_bits = (~attn_bits & attn_acks & ATTN_STATE_BITS) &
		p_sb_attn_sw->known_attn;

	if ((asserted_bits & ~0x100) || (deasserted_bits & ~0x100)) {
		DP_INFO(p_hwfn,
			"Attention: Index: 0x%04x, Bits: 0x%08x, Acks: 0x%08x, asserted: 0x%04x, De-asserted 0x%04x [Prev. known: 0x%04x]\n",
			index, attn_bits, attn_acks, asserted_bits,
			deasserted_bits, p_sb_attn_sw->known_attn);
	} else if (asserted_bits == 0x100) {
		DP_INFO(p_hwfn, "MFW indication via attention\n");
	} else {
		DP_VERBOSE(p_hwfn, NETIF_MSG_INTR,
			   "MFW indication [deassertion]\n");
	}

	if (asserted_bits) {
		rc = qed_int_assertion(p_hwfn, asserted_bits);
		if (rc)
			return rc;
	}

	if (deasserted_bits)
		rc = qed_int_deassertion(p_hwfn, deasserted_bits);

	return rc;
}