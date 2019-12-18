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
typedef  scalar_t__ u32 ;
struct qe_mux {int /*<<< orphan*/  cmxsi1syr; } ;
typedef  enum qe_clock { ____Placeholder_qe_clock } qe_clock ;
typedef  enum comm_dir { ____Placeholder_comm_dir } comm_dir ;
struct TYPE_2__ {struct qe_mux qmx; } ;

/* Variables and functions */
 int COMM_DIR_RX ; 
 int COMM_DIR_TX ; 
 int EINVAL ; 
 scalar_t__ QE_CMXUCR_TX_CLK_SRC_MASK ; 
 scalar_t__ UCC_TDM_NUM ; 
 int /*<<< orphan*/  qe_clrsetbits32 (int /*<<< orphan*/ *,scalar_t__,int) ; 
 TYPE_1__* qe_immr ; 
 scalar_t__ ucc_get_tdm_sync_shift (int,scalar_t__) ; 
 int ucc_get_tdm_sync_source (scalar_t__,int,int) ; 

int ucc_set_tdm_rxtx_sync(u32 tdm_num, enum qe_clock clock,
			  enum comm_dir mode)
{
	int source;
	u32 shift;
	struct qe_mux *qe_mux_reg;

	qe_mux_reg = &qe_immr->qmx;

	if (tdm_num >= UCC_TDM_NUM)
		return -EINVAL;

	/* The communications direction must be RX or TX */
	if (mode != COMM_DIR_RX && mode != COMM_DIR_TX)
		return -EINVAL;

	source = ucc_get_tdm_sync_source(tdm_num, clock, mode);
	if (source < 0)
		return -EINVAL;

	shift = ucc_get_tdm_sync_shift(mode, tdm_num);

	qe_clrsetbits32(&qe_mux_reg->cmxsi1syr,
			QE_CMXUCR_TX_CLK_SRC_MASK << shift,
			source << shift);

	return 0;
}