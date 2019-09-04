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
typedef  size_t u32 ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {int dummy; } ;
struct dbg_dump_split_hdr {int /*<<< orphan*/  hdr; } ;
struct dbg_array {size_t size_in_dwords; int /*<<< orphan*/ * ptr; } ;
typedef  enum init_split_types { ____Placeholder_init_split_types } init_split_types ;
struct TYPE_2__ {size_t size_in_dwords; int /*<<< orphan*/ * ptr; } ;

/* Variables and functions */
 size_t BIN_BUF_DBG_DUMP_MEM ; 
 int /*<<< orphan*/  DBG_DUMP_SPLIT_HDR_DATA_SIZE ; 
 int /*<<< orphan*/  DBG_DUMP_SPLIT_HDR_SPLIT_TYPE_ID ; 
 int /*<<< orphan*/  DP_NOTICE (struct qed_hwfn*,char*) ; 
 void* GET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SPLIT_TYPE_NONE ; 
 size_t qed_grc_dump_mem_entries (struct qed_hwfn*,struct qed_ptt*,struct dbg_array,size_t*,int) ; 
 TYPE_1__* s_dbg_arrays ; 

__attribute__((used)) static u32 qed_grc_dump_memories(struct qed_hwfn *p_hwfn,
				 struct qed_ptt *p_ptt,
				 u32 *dump_buf, bool dump)
{
	u32 offset = 0, input_offset = 0;

	while (input_offset <
	       s_dbg_arrays[BIN_BUF_DBG_DUMP_MEM].size_in_dwords) {
		const struct dbg_dump_split_hdr *split_hdr;
		struct dbg_array curr_input_mems_arr;
		enum init_split_types split_type;
		u32 split_data_size;

		split_hdr = (const struct dbg_dump_split_hdr *)
			&s_dbg_arrays[BIN_BUF_DBG_DUMP_MEM].ptr[input_offset++];
		split_type =
			GET_FIELD(split_hdr->hdr,
				  DBG_DUMP_SPLIT_HDR_SPLIT_TYPE_ID);
		split_data_size =
			GET_FIELD(split_hdr->hdr,
				  DBG_DUMP_SPLIT_HDR_DATA_SIZE);
		curr_input_mems_arr.ptr =
			&s_dbg_arrays[BIN_BUF_DBG_DUMP_MEM].ptr[input_offset];
		curr_input_mems_arr.size_in_dwords = split_data_size;

		if (split_type == SPLIT_TYPE_NONE)
			offset += qed_grc_dump_mem_entries(p_hwfn,
							   p_ptt,
							   curr_input_mems_arr,
							   dump_buf + offset,
							   dump);
		else
			DP_NOTICE(p_hwfn,
				  "Dumping split memories is currently not supported\n");

		input_offset += split_data_size;
	}

	return offset;
}