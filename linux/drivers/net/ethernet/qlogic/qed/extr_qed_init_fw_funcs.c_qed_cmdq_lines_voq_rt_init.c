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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct qed_hwfn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OVERWRITE_RT_REG (struct qed_hwfn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PBF_CMDQ_LINES_RT_OFFSET (scalar_t__) ; 
 scalar_t__ QM_REG_VOQCRDLINE_RT_OFFSET ; 
 scalar_t__ QM_REG_VOQINITCRDLINE_RT_OFFSET ; 
 int /*<<< orphan*/  QM_VOQ_LINE_CRD (scalar_t__) ; 
 int /*<<< orphan*/  STORE_RT_REG (struct qed_hwfn*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qed_cmdq_lines_voq_rt_init(struct qed_hwfn *p_hwfn,
				       u8 ext_voq, u16 cmdq_lines)
{
	u32 qm_line_crd = QM_VOQ_LINE_CRD(cmdq_lines);

	OVERWRITE_RT_REG(p_hwfn, PBF_CMDQ_LINES_RT_OFFSET(ext_voq),
			 (u32)cmdq_lines);
	STORE_RT_REG(p_hwfn, QM_REG_VOQCRDLINE_RT_OFFSET + ext_voq,
		     qm_line_crd);
	STORE_RT_REG(p_hwfn, QM_REG_VOQINITCRDLINE_RT_OFFSET + ext_voq,
		     qm_line_crd);
}