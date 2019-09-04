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
typedef  size_t u8 ;
typedef  size_t u32 ;
typedef  size_t u16 ;
struct user_dbg_array {size_t* ptr; } ;
struct qed_hwfn {int dummy; } ;
struct dbg_attn_reg_result {size_t block_attn_offset; int sts_val; int mask_val; int /*<<< orphan*/  data; } ;
struct dbg_attn_block_result {size_t block_id; size_t names_offset; struct dbg_attn_reg_result* reg_results; int /*<<< orphan*/  data; } ;
struct dbg_attn_bit_mapping {int /*<<< orphan*/  data; } ;
typedef  enum dbg_status { ____Placeholder_dbg_status } dbg_status ;
typedef  enum dbg_attn_type { ____Placeholder_dbg_attn_type } dbg_attn_type ;
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 int ATTN_TYPE_INTERRUPT ; 
 size_t BIN_BUF_DBG_ATTN_INDEXES ; 
 size_t BIN_BUF_DBG_ATTN_NAME_OFFSETS ; 
 size_t BIN_BUF_DBG_PARSING_STRINGS ; 
 int BIT (size_t) ; 
 int /*<<< orphan*/  DBG_ATTN_BIT_MAPPING_IS_UNUSED_BIT_CNT ; 
 int /*<<< orphan*/  DBG_ATTN_BIT_MAPPING_VAL ; 
 int /*<<< orphan*/  DBG_ATTN_BLOCK_RESULT_ATTN_TYPE ; 
 int /*<<< orphan*/  DBG_ATTN_BLOCK_RESULT_NUM_REGS ; 
 int /*<<< orphan*/  DBG_ATTN_REG_RESULT_NUM_REG_ATTN ; 
 int /*<<< orphan*/  DBG_ATTN_REG_RESULT_STS_ADDRESS ; 
 int DBG_STATUS_DBG_ARRAY_NOT_SET ; 
 int DBG_STATUS_OK ; 
 int /*<<< orphan*/  DP_NOTICE (struct qed_hwfn*,char*,char const*,char const*,char const*,size_t,size_t,char const*) ; 
 size_t GET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* s_block_info_arr ; 
 struct user_dbg_array* s_user_dbg_arrays ; 

enum dbg_status qed_dbg_parse_attn(struct qed_hwfn *p_hwfn,
				   struct dbg_attn_block_result *results)
{
	struct user_dbg_array *block_attn, *pstrings;
	const u32 *block_attn_name_offsets;
	enum dbg_attn_type attn_type;
	const char *block_name;
	u8 num_regs, i, j;

	num_regs = GET_FIELD(results->data, DBG_ATTN_BLOCK_RESULT_NUM_REGS);
	attn_type = (enum dbg_attn_type)
		    GET_FIELD(results->data,
			      DBG_ATTN_BLOCK_RESULT_ATTN_TYPE);
	block_name = s_block_info_arr[results->block_id].name;

	if (!s_user_dbg_arrays[BIN_BUF_DBG_ATTN_INDEXES].ptr ||
	    !s_user_dbg_arrays[BIN_BUF_DBG_ATTN_NAME_OFFSETS].ptr ||
	    !s_user_dbg_arrays[BIN_BUF_DBG_PARSING_STRINGS].ptr)
		return DBG_STATUS_DBG_ARRAY_NOT_SET;

	block_attn = &s_user_dbg_arrays[BIN_BUF_DBG_ATTN_NAME_OFFSETS];
	block_attn_name_offsets = &block_attn->ptr[results->names_offset];

	/* Go over registers with a non-zero attention status */
	for (i = 0; i < num_regs; i++) {
		struct dbg_attn_bit_mapping *bit_mapping;
		struct dbg_attn_reg_result *reg_result;
		u8 num_reg_attn, bit_idx = 0;

		reg_result = &results->reg_results[i];
		num_reg_attn = GET_FIELD(reg_result->data,
					 DBG_ATTN_REG_RESULT_NUM_REG_ATTN);
		block_attn = &s_user_dbg_arrays[BIN_BUF_DBG_ATTN_INDEXES];
		bit_mapping = &((struct dbg_attn_bit_mapping *)
				block_attn->ptr)[reg_result->block_attn_offset];

		pstrings = &s_user_dbg_arrays[BIN_BUF_DBG_PARSING_STRINGS];

		/* Go over attention status bits */
		for (j = 0; j < num_reg_attn; j++) {
			u16 attn_idx_val = GET_FIELD(bit_mapping[j].data,
						     DBG_ATTN_BIT_MAPPING_VAL);
			const char *attn_name, *attn_type_str, *masked_str;
			u32 attn_name_offset, sts_addr;

			/* Check if bit mask should be advanced (due to unused
			 * bits).
			 */
			if (GET_FIELD(bit_mapping[j].data,
				      DBG_ATTN_BIT_MAPPING_IS_UNUSED_BIT_CNT)) {
				bit_idx += (u8)attn_idx_val;
				continue;
			}

			/* Check current bit index */
			if (!(reg_result->sts_val & BIT(bit_idx))) {
				bit_idx++;
				continue;
			}

			/* Find attention name */
			attn_name_offset =
				block_attn_name_offsets[attn_idx_val];
			attn_name = &((const char *)
				      pstrings->ptr)[attn_name_offset];
			attn_type_str = attn_type == ATTN_TYPE_INTERRUPT ?
					"Interrupt" : "Parity";
			masked_str = reg_result->mask_val & BIT(bit_idx) ?
				     " [masked]" : "";
			sts_addr = GET_FIELD(reg_result->data,
					     DBG_ATTN_REG_RESULT_STS_ADDRESS);
			DP_NOTICE(p_hwfn,
				  "%s (%s) : %s [address 0x%08x, bit %d]%s\n",
				  block_name, attn_type_str, attn_name,
				  sts_addr, bit_idx, masked_str);

			bit_idx++;
		}
	}

	return DBG_STATUS_OK;
}