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
typedef  void* u8 ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct dbg_idle_chk_rule_parsing_data {int /*<<< orphan*/  data; } ;
struct dbg_idle_chk_result_reg_hdr {int start_entry; scalar_t__ size; int /*<<< orphan*/  data; } ;
struct dbg_idle_chk_result_hdr {size_t rule_id; size_t severity; scalar_t__ num_dumped_cond_regs; scalar_t__ num_dumped_info_regs; int mem_entry_id; } ;
struct TYPE_2__ {int /*<<< orphan*/ * ptr; } ;

/* Variables and functions */
 size_t BIN_BUF_DBG_IDLE_CHK_PARSING_DATA ; 
 size_t BIN_BUF_DBG_PARSING_STRINGS ; 
 int /*<<< orphan*/  BYTES_TO_DWORDS (int) ; 
 int /*<<< orphan*/  DBG_IDLE_CHK_RESULT_REG_HDR_IS_MEM ; 
 int /*<<< orphan*/  DBG_IDLE_CHK_RESULT_REG_HDR_REG_ID ; 
 int /*<<< orphan*/  DBG_IDLE_CHK_RULE_PARSING_DATA_HAS_FW_MSG ; 
 int /*<<< orphan*/  DBG_IDLE_CHK_RULE_PARSING_DATA_STR_OFFSET ; 
 void* GET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t IDLE_CHK_SEVERITY_ERROR ; 
 size_t IDLE_CHK_SEVERITY_ERROR_NO_TRAFFIC ; 
 size_t MAX_DBG_IDLE_CHK_SEVERITY_TYPES ; 
 int /*<<< orphan*/  qed_get_buf_ptr (char*,scalar_t__) ; 
 char** s_idle_chk_severity_str ; 
 TYPE_1__* s_user_dbg_arrays ; 
 scalar_t__ sprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static u32 qed_parse_idle_chk_dump_rules(u32 *dump_buf,
					 u32 *dump_buf_end,
					 u32 num_rules,
					 bool print_fw_idle_chk,
					 char *results_buf,
					 u32 *num_errors, u32 *num_warnings)
{
	/* Offset in results_buf in bytes */
	u32 results_offset = 0;

	u32 rule_idx;
	u16 i, j;

	*num_errors = 0;
	*num_warnings = 0;

	/* Go over dumped results */
	for (rule_idx = 0; rule_idx < num_rules && dump_buf < dump_buf_end;
	     rule_idx++) {
		const struct dbg_idle_chk_rule_parsing_data *rule_parsing_data;
		struct dbg_idle_chk_result_hdr *hdr;
		const char *parsing_str, *lsi_msg;
		u32 parsing_str_offset;
		bool has_fw_msg;
		u8 curr_reg_id;

		hdr = (struct dbg_idle_chk_result_hdr *)dump_buf;
		rule_parsing_data =
			(const struct dbg_idle_chk_rule_parsing_data *)
			&s_user_dbg_arrays[BIN_BUF_DBG_IDLE_CHK_PARSING_DATA].
			ptr[hdr->rule_id];
		parsing_str_offset =
			GET_FIELD(rule_parsing_data->data,
				  DBG_IDLE_CHK_RULE_PARSING_DATA_STR_OFFSET);
		has_fw_msg =
			GET_FIELD(rule_parsing_data->data,
				DBG_IDLE_CHK_RULE_PARSING_DATA_HAS_FW_MSG) > 0;
		parsing_str =
			&((const char *)
			s_user_dbg_arrays[BIN_BUF_DBG_PARSING_STRINGS].ptr)
			[parsing_str_offset];
		lsi_msg = parsing_str;
		curr_reg_id = 0;

		if (hdr->severity >= MAX_DBG_IDLE_CHK_SEVERITY_TYPES)
			return 0;

		/* Skip rule header */
		dump_buf += BYTES_TO_DWORDS(sizeof(*hdr));

		/* Update errors/warnings count */
		if (hdr->severity == IDLE_CHK_SEVERITY_ERROR ||
		    hdr->severity == IDLE_CHK_SEVERITY_ERROR_NO_TRAFFIC)
			(*num_errors)++;
		else
			(*num_warnings)++;

		/* Print rule severity */
		results_offset +=
		    sprintf(qed_get_buf_ptr(results_buf,
					    results_offset), "%s: ",
			    s_idle_chk_severity_str[hdr->severity]);

		/* Print rule message */
		if (has_fw_msg)
			parsing_str += strlen(parsing_str) + 1;
		results_offset +=
		    sprintf(qed_get_buf_ptr(results_buf,
					    results_offset), "%s.",
			    has_fw_msg &&
			    print_fw_idle_chk ? parsing_str : lsi_msg);
		parsing_str += strlen(parsing_str) + 1;

		/* Print register values */
		results_offset +=
		    sprintf(qed_get_buf_ptr(results_buf,
					    results_offset), " Registers:");
		for (i = 0;
		     i < hdr->num_dumped_cond_regs + hdr->num_dumped_info_regs;
		     i++) {
			struct dbg_idle_chk_result_reg_hdr *reg_hdr;
			bool is_mem;
			u8 reg_id;

			reg_hdr =
				(struct dbg_idle_chk_result_reg_hdr *)dump_buf;
			is_mem = GET_FIELD(reg_hdr->data,
					   DBG_IDLE_CHK_RESULT_REG_HDR_IS_MEM);
			reg_id = GET_FIELD(reg_hdr->data,
					   DBG_IDLE_CHK_RESULT_REG_HDR_REG_ID);

			/* Skip reg header */
			dump_buf += BYTES_TO_DWORDS(sizeof(*reg_hdr));

			/* Skip register names until the required reg_id is
			 * reached.
			 */
			for (; reg_id > curr_reg_id;
			     curr_reg_id++,
			     parsing_str += strlen(parsing_str) + 1);

			results_offset +=
			    sprintf(qed_get_buf_ptr(results_buf,
						    results_offset), " %s",
				    parsing_str);
			if (i < hdr->num_dumped_cond_regs && is_mem)
				results_offset +=
				    sprintf(qed_get_buf_ptr(results_buf,
							    results_offset),
					    "[%d]", hdr->mem_entry_id +
					    reg_hdr->start_entry);
			results_offset +=
			    sprintf(qed_get_buf_ptr(results_buf,
						    results_offset), "=");
			for (j = 0; j < reg_hdr->size; j++, dump_buf++) {
				results_offset +=
				    sprintf(qed_get_buf_ptr(results_buf,
							    results_offset),
					    "0x%x", *dump_buf);
				if (j < reg_hdr->size - 1)
					results_offset +=
					    sprintf(qed_get_buf_ptr
						    (results_buf,
						     results_offset), ",");
			}
		}

		results_offset +=
		    sprintf(qed_get_buf_ptr(results_buf, results_offset), "\n");
	}

	/* Check if end of dump buffer was exceeded */
	if (dump_buf > dump_buf_end)
		return 0;

	return results_offset;
}