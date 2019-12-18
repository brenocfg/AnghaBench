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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct intr_info {int member_0; char* member_1; int member_2; int member_3; } ;
struct csio_hw {int dummy; } ;

/* Variables and functions */
#define  EGRESS_SIZE_ERR_F 141 
#define  ERR_BAD_DB_PIDX0_F 140 
#define  ERR_BAD_DB_PIDX1_F 139 
#define  ERR_BAD_DB_PIDX2_F 138 
#define  ERR_BAD_DB_PIDX3_F 137 
#define  ERR_CPL_EXCEED_IQE_SIZE_F 136 
#define  ERR_CPL_OPCODE_0_F 135 
#define  ERR_DATA_CPL_ON_HIGH_QID0_F 134 
#define  ERR_DATA_CPL_ON_HIGH_QID1_F 133 
#define  ERR_DROPPED_DB_F 132 
#define  ERR_EGR_CTXT_PRIO_F 131 
#define  ERR_ING_CTXT_PRIO_F 130 
#define  ERR_INVALID_CIDX_INC_F 129 
#define  INGRESS_SIZE_ERR_F 128 
 int /*<<< orphan*/  SGE_INT_CAUSE1_A ; 
 int /*<<< orphan*/  SGE_INT_CAUSE2_A ; 
 int /*<<< orphan*/  SGE_INT_CAUSE3_A ; 
 int /*<<< orphan*/  csio_fatal (struct csio_hw*,char*,unsigned long long) ; 
 int csio_handle_intr_status (struct csio_hw*,int /*<<< orphan*/ ,struct intr_info*) ; 
 int /*<<< orphan*/  csio_hw_fatal_err (struct csio_hw*) ; 
 scalar_t__ csio_rd_reg32 (struct csio_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csio_wr_reg32 (struct csio_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void csio_sge_intr_handler(struct csio_hw *hw)
{
	uint64_t v;

	static struct intr_info sge_intr_info[] = {
		{ ERR_CPL_EXCEED_IQE_SIZE_F,
		  "SGE received CPL exceeding IQE size", -1, 1 },
		{ ERR_INVALID_CIDX_INC_F,
		  "SGE GTS CIDX increment too large", -1, 0 },
		{ ERR_CPL_OPCODE_0_F, "SGE received 0-length CPL", -1, 0 },
		{ ERR_DROPPED_DB_F, "SGE doorbell dropped", -1, 0 },
		{ ERR_DATA_CPL_ON_HIGH_QID1_F | ERR_DATA_CPL_ON_HIGH_QID0_F,
		  "SGE IQID > 1023 received CPL for FL", -1, 0 },
		{ ERR_BAD_DB_PIDX3_F, "SGE DBP 3 pidx increment too large", -1,
		  0 },
		{ ERR_BAD_DB_PIDX2_F, "SGE DBP 2 pidx increment too large", -1,
		  0 },
		{ ERR_BAD_DB_PIDX1_F, "SGE DBP 1 pidx increment too large", -1,
		  0 },
		{ ERR_BAD_DB_PIDX0_F, "SGE DBP 0 pidx increment too large", -1,
		  0 },
		{ ERR_ING_CTXT_PRIO_F,
		  "SGE too many priority ingress contexts", -1, 0 },
		{ ERR_EGR_CTXT_PRIO_F,
		  "SGE too many priority egress contexts", -1, 0 },
		{ INGRESS_SIZE_ERR_F, "SGE illegal ingress QID", -1, 0 },
		{ EGRESS_SIZE_ERR_F, "SGE illegal egress QID", -1, 0 },
		{ 0, NULL, 0, 0 }
	};

	v = (uint64_t)csio_rd_reg32(hw, SGE_INT_CAUSE1_A) |
	    ((uint64_t)csio_rd_reg32(hw, SGE_INT_CAUSE2_A) << 32);
	if (v) {
		csio_fatal(hw, "SGE parity error (%#llx)\n",
			    (unsigned long long)v);
		csio_wr_reg32(hw, (uint32_t)(v & 0xFFFFFFFF),
						SGE_INT_CAUSE1_A);
		csio_wr_reg32(hw, (uint32_t)(v >> 32), SGE_INT_CAUSE2_A);
	}

	v |= csio_handle_intr_status(hw, SGE_INT_CAUSE3_A, sge_intr_info);

	if (csio_handle_intr_status(hw, SGE_INT_CAUSE3_A, sge_intr_info) ||
	    v != 0)
		csio_hw_fatal_err(hw);
}