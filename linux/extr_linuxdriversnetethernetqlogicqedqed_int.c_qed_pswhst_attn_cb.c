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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct qed_hwfn {int /*<<< orphan*/  cdev; int /*<<< orphan*/  p_dpc_ptt; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATTENTION_INCORRECT_ACCESS_BYTE_EN ; 
 int /*<<< orphan*/  ATTENTION_INCORRECT_ACCESS_CLIENT ; 
 int /*<<< orphan*/  ATTENTION_INCORRECT_ACCESS_PF_ID ; 
 int /*<<< orphan*/  ATTENTION_INCORRECT_ACCESS_VF_ID ; 
 int /*<<< orphan*/  ATTENTION_INCORRECT_ACCESS_VF_VALID ; 
 int /*<<< orphan*/  ATTENTION_INCORRECT_ACCESS_WR ; 
 int /*<<< orphan*/  DP_INFO (int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ GET_FIELD (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PSWHST_REG_INCORRECT_ACCESS_ADDRESS ; 
 int /*<<< orphan*/  PSWHST_REG_INCORRECT_ACCESS_DATA ; 
 int /*<<< orphan*/  PSWHST_REG_INCORRECT_ACCESS_LENGTH ; 
 int /*<<< orphan*/  PSWHST_REG_INCORRECT_ACCESS_VALID ; 
 int QED_PSWHST_ATTENTION_INCORRECT_ACCESS ; 
 int qed_rd (struct qed_hwfn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qed_pswhst_attn_cb(struct qed_hwfn *p_hwfn)
{
	u32 tmp = qed_rd(p_hwfn, p_hwfn->p_dpc_ptt,
			 PSWHST_REG_INCORRECT_ACCESS_VALID);

	if (tmp & QED_PSWHST_ATTENTION_INCORRECT_ACCESS) {
		u32 addr, data, length;

		addr = qed_rd(p_hwfn, p_hwfn->p_dpc_ptt,
			      PSWHST_REG_INCORRECT_ACCESS_ADDRESS);
		data = qed_rd(p_hwfn, p_hwfn->p_dpc_ptt,
			      PSWHST_REG_INCORRECT_ACCESS_DATA);
		length = qed_rd(p_hwfn, p_hwfn->p_dpc_ptt,
				PSWHST_REG_INCORRECT_ACCESS_LENGTH);

		DP_INFO(p_hwfn->cdev,
			"Incorrect access to %08x of length %08x - PF [%02x] VF [%04x] [valid %02x] client [%02x] write [%02x] Byte-Enable [%04x] [%08x]\n",
			addr, length,
			(u8) GET_FIELD(data, ATTENTION_INCORRECT_ACCESS_PF_ID),
			(u8) GET_FIELD(data, ATTENTION_INCORRECT_ACCESS_VF_ID),
			(u8) GET_FIELD(data,
				       ATTENTION_INCORRECT_ACCESS_VF_VALID),
			(u8) GET_FIELD(data,
				       ATTENTION_INCORRECT_ACCESS_CLIENT),
			(u8) GET_FIELD(data, ATTENTION_INCORRECT_ACCESS_WR),
			(u8) GET_FIELD(data,
				       ATTENTION_INCORRECT_ACCESS_BYTE_EN),
			data);
	}

	return 0;
}