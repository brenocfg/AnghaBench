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
struct qed_ptt {int dummy; } ;
struct qed_hwfn {int dummy; } ;

/* Variables and functions */
 int BYTES_TO_DWORDS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RDIF_REG_DEBUG_ERROR_INFO ; 
 int /*<<< orphan*/  RDIF_REG_DEBUG_ERROR_INFO_SIZE ; 
 int /*<<< orphan*/  SPLIT_TYPE_NONE ; 
 int /*<<< orphan*/  TDIF_REG_DEBUG_ERROR_INFO ; 
 int /*<<< orphan*/  TDIF_REG_DEBUG_ERROR_INFO_SIZE ; 
 int qed_grc_dump_reg_entry_skip (struct qed_hwfn*,struct qed_ptt*,int*,int,int,int /*<<< orphan*/ ,int,int) ; 
 int qed_grc_dump_regs_hdr (int*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 qed_grc_dump_special_regs(struct qed_hwfn *p_hwfn,
				     struct qed_ptt *p_ptt,
				     u32 *dump_buf, bool dump)
{
	u32 offset = 0, addr;

	offset += qed_grc_dump_regs_hdr(dump_buf,
					dump, 2, SPLIT_TYPE_NONE, 0,
					NULL, NULL);

	/* Dump R/TDIF_REG_DEBUG_ERROR_INFO_SIZE (every 8'th register should be
	 * skipped).
	 */
	addr = BYTES_TO_DWORDS(RDIF_REG_DEBUG_ERROR_INFO);
	offset += qed_grc_dump_reg_entry_skip(p_hwfn,
					      p_ptt,
					      dump_buf + offset,
					      dump,
					      addr,
					      RDIF_REG_DEBUG_ERROR_INFO_SIZE,
					      7,
					      1);
	addr = BYTES_TO_DWORDS(TDIF_REG_DEBUG_ERROR_INFO);
	offset +=
	    qed_grc_dump_reg_entry_skip(p_hwfn,
					p_ptt,
					dump_buf + offset,
					dump,
					addr,
					TDIF_REG_DEBUG_ERROR_INFO_SIZE,
					7,
					1);

	return offset;
}