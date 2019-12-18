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
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {int dummy; } ;
struct dbg_idle_chk_rule {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  data; } ;
struct dbg_idle_chk_cond_hdr {int data_size; TYPE_1__ mode; } ;
struct TYPE_4__ {int size_in_dwords; int /*<<< orphan*/ * ptr; } ;

/* Variables and functions */
 size_t BIN_BUF_DBG_IDLE_CHK_RULES ; 
 int /*<<< orphan*/  DBG_MODE_HDR_EVAL_MODE ; 
 int /*<<< orphan*/  DBG_MODE_HDR_MODES_BUF_OFFSET ; 
 scalar_t__ GET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IDLE_CHK_RULE_SIZE_DWORDS ; 
 int qed_dump_common_global_params (struct qed_hwfn*,struct qed_ptt*,int*,int,int) ; 
 int qed_dump_last_section (int*,int,int) ; 
 int qed_dump_num_param (int*,int,char*,int) ; 
 int qed_dump_section_hdr (int*,int,char*,int) ; 
 int qed_dump_str_param (int*,int,char*,char*) ; 
 int qed_idle_chk_dump_rule_entries (struct qed_hwfn*,struct qed_ptt*,int*,int,struct dbg_idle_chk_rule const*,int,int*) ; 
 int qed_is_mode_match (struct qed_hwfn*,scalar_t__*) ; 
 TYPE_2__* s_dbg_arrays ; 

__attribute__((used)) static u32 qed_idle_chk_dump(struct qed_hwfn *p_hwfn,
			     struct qed_ptt *p_ptt, u32 *dump_buf, bool dump)
{
	u32 num_failing_rules_offset, offset = 0, input_offset = 0;
	u32 num_failing_rules = 0;

	/* Dump global params */
	offset += qed_dump_common_global_params(p_hwfn,
						p_ptt,
						dump_buf + offset, dump, 1);
	offset += qed_dump_str_param(dump_buf + offset,
				     dump, "dump-type", "idle-chk");

	/* Dump idle check section header with a single parameter */
	offset += qed_dump_section_hdr(dump_buf + offset, dump, "idle_chk", 1);
	num_failing_rules_offset = offset;
	offset += qed_dump_num_param(dump_buf + offset, dump, "num_rules", 0);

	while (input_offset <
	       s_dbg_arrays[BIN_BUF_DBG_IDLE_CHK_RULES].size_in_dwords) {
		const struct dbg_idle_chk_cond_hdr *cond_hdr =
			(const struct dbg_idle_chk_cond_hdr *)
			&s_dbg_arrays[BIN_BUF_DBG_IDLE_CHK_RULES].ptr
			[input_offset++];
		bool eval_mode, mode_match = true;
		u32 curr_failing_rules;
		u16 modes_buf_offset;

		/* Check mode */
		eval_mode = GET_FIELD(cond_hdr->mode.data,
				      DBG_MODE_HDR_EVAL_MODE) > 0;
		if (eval_mode) {
			modes_buf_offset =
				GET_FIELD(cond_hdr->mode.data,
					  DBG_MODE_HDR_MODES_BUF_OFFSET);
			mode_match = qed_is_mode_match(p_hwfn,
						       &modes_buf_offset);
		}

		if (mode_match) {
			offset +=
			    qed_idle_chk_dump_rule_entries(p_hwfn,
				p_ptt,
				dump_buf + offset,
				dump,
				(const struct dbg_idle_chk_rule *)
				&s_dbg_arrays[BIN_BUF_DBG_IDLE_CHK_RULES].
				ptr[input_offset],
				cond_hdr->data_size / IDLE_CHK_RULE_SIZE_DWORDS,
				&curr_failing_rules);
			num_failing_rules += curr_failing_rules;
		}

		input_offset += cond_hdr->data_size;
	}

	/* Overwrite num_rules parameter */
	if (dump)
		qed_dump_num_param(dump_buf + num_failing_rules_offset,
				   dump, "num_rules", num_failing_rules);

	/* Dump last section */
	offset += qed_dump_last_section(dump_buf, offset, dump);

	return offset;
}