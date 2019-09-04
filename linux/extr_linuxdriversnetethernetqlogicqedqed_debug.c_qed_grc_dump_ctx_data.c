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
typedef  size_t u8 ;
typedef  int u32 ;
struct storm_defs {int /*<<< orphan*/  cm_ctx_wr_addr; int /*<<< orphan*/  letter; } ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {int dummy; } ;

/* Variables and functions */
 int BYTES_IN_DWORD ; 
 int qed_grc_dump_mem_hdr (struct qed_hwfn*,int*,int,char const*,int /*<<< orphan*/ ,int,int,int,char const*,int,int /*<<< orphan*/ ) ; 
 int qed_rd (struct qed_hwfn*,struct qed_ptt*,int) ; 
 int /*<<< orphan*/  qed_wr (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ,int) ; 
 struct storm_defs* s_storm_defs ; 

__attribute__((used)) static u32 qed_grc_dump_ctx_data(struct qed_hwfn *p_hwfn,
				 struct qed_ptt *p_ptt,
				 u32 *dump_buf,
				 bool dump,
				 const char *name,
				 u32 num_lids,
				 u32 lid_size,
				 u32 rd_reg_addr,
				 u8 storm_id)
{
	struct storm_defs *storm = &s_storm_defs[storm_id];
	u32 i, lid, total_size, offset = 0;

	if (!lid_size)
		return 0;

	lid_size *= BYTES_IN_DWORD;
	total_size = num_lids * lid_size;

	offset += qed_grc_dump_mem_hdr(p_hwfn,
				       dump_buf + offset,
				       dump,
				       name,
				       0,
				       total_size,
				       lid_size * 32,
				       false, name, true, storm->letter);

	if (!dump)
		return offset + total_size;

	/* Dump context data */
	for (lid = 0; lid < num_lids; lid++) {
		for (i = 0; i < lid_size; i++, offset++) {
			qed_wr(p_hwfn,
			       p_ptt, storm->cm_ctx_wr_addr, (i << 9) | lid);
			*(dump_buf + offset) = qed_rd(p_hwfn,
						      p_ptt, rd_reg_addr);
		}
	}

	return offset;
}