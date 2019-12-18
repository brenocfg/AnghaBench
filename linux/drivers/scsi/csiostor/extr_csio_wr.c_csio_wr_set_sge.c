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
struct csio_sge {int csio_fl_align; int /*<<< orphan*/ * timer_val; int /*<<< orphan*/ * counter_val; int /*<<< orphan*/  sge_control; } ;
struct csio_wrm {struct csio_sge sge; } ;
struct csio_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSIO_SET_FLBUF_SIZE (struct csio_hw*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSIO_SGE_DBFIFO_INT_THRESH ; 
 int /*<<< orphan*/  CSIO_SGE_FLBUF_SIZE1 ; 
 int CSIO_SGE_FLBUF_SIZE2 ; 
 int CSIO_SGE_FLBUF_SIZE3 ; 
 int /*<<< orphan*/  CSIO_SGE_FLBUF_SIZE4 ; 
 int /*<<< orphan*/  CSIO_SGE_FLBUF_SIZE5 ; 
 int /*<<< orphan*/  CSIO_SGE_FLBUF_SIZE6 ; 
 int /*<<< orphan*/  CSIO_SGE_FLBUF_SIZE7 ; 
 int /*<<< orphan*/  CSIO_SGE_FLBUF_SIZE8 ; 
 int CSIO_SGE_FL_SIZE_REGS ; 
 int /*<<< orphan*/  CSIO_SGE_INT_CNT_VAL_0 ; 
 int /*<<< orphan*/  CSIO_SGE_INT_CNT_VAL_1 ; 
 int /*<<< orphan*/  CSIO_SGE_INT_CNT_VAL_2 ; 
 int /*<<< orphan*/  CSIO_SGE_INT_CNT_VAL_3 ; 
 int /*<<< orphan*/  CSIO_SGE_TIMER_VAL_0 ; 
 int /*<<< orphan*/  CSIO_SGE_TIMER_VAL_1 ; 
 int /*<<< orphan*/  CSIO_SGE_TIMER_VAL_2 ; 
 int /*<<< orphan*/  CSIO_SGE_TIMER_VAL_3 ; 
 int /*<<< orphan*/  CSIO_SGE_TIMER_VAL_4 ; 
 int /*<<< orphan*/  CSIO_SGE_TIMER_VAL_5 ; 
 int /*<<< orphan*/  ENABLE_DROP_F ; 
 int /*<<< orphan*/  HP_INT_THRESH_T5_V (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LP_INT_THRESH_T5_M ; 
 int /*<<< orphan*/  LP_INT_THRESH_T5_V (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RXPKTCPLMODE_F ; 
 int /*<<< orphan*/  SGE_CONTROL_A ; 
 int /*<<< orphan*/  SGE_DBFIFO_STATUS2_A ; 
 int /*<<< orphan*/  SGE_DBFIFO_STATUS_A ; 
 int /*<<< orphan*/  SGE_DOORBELL_CONTROL_A ; 
 int /*<<< orphan*/  SGE_FL_BUFFER_SIZE2_A ; 
 int /*<<< orphan*/  SGE_FL_BUFFER_SIZE3_A ; 
 int /*<<< orphan*/  SGE_INGRESS_RX_THRESHOLD_A ; 
 int /*<<< orphan*/  SGE_TIMER_VALUE_0_AND_1_A ; 
 int /*<<< orphan*/  SGE_TIMER_VALUE_2_AND_3_A ; 
 int /*<<< orphan*/  SGE_TIMER_VALUE_4_AND_5_A ; 
 int THRESHOLD_0_V (int /*<<< orphan*/ ) ; 
 int THRESHOLD_1_V (int /*<<< orphan*/ ) ; 
 int THRESHOLD_2_V (int /*<<< orphan*/ ) ; 
 int THRESHOLD_3_V (int /*<<< orphan*/ ) ; 
 int TIMERVALUE0_V (int /*<<< orphan*/ ) ; 
 int TIMERVALUE1_V (int /*<<< orphan*/ ) ; 
 int TIMERVALUE2_V (int /*<<< orphan*/ ) ; 
 int TIMERVALUE3_V (int /*<<< orphan*/ ) ; 
 int TIMERVALUE4_V (int /*<<< orphan*/ ) ; 
 int TIMERVALUE5_V (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csio_get_flbuf_size (struct csio_hw*,struct csio_sge*,int) ; 
 struct csio_wrm* csio_hw_to_wrm (struct csio_hw*) ; 
 int /*<<< orphan*/  csio_init_intr_coalesce_parms (struct csio_hw*) ; 
 int /*<<< orphan*/  csio_rd_reg32 (struct csio_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csio_set_reg_field (struct csio_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csio_us_to_core_ticks (struct csio_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csio_wr_reg32 (struct csio_hw*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
csio_wr_set_sge(struct csio_hw *hw)
{
	struct csio_wrm *wrm = csio_hw_to_wrm(hw);
	struct csio_sge *sge = &wrm->sge;
	int i;

	/*
	 * Set up our basic SGE mode to deliver CPL messages to our Ingress
	 * Queue and Packet Date to the Free List.
	 */
	csio_set_reg_field(hw, SGE_CONTROL_A, RXPKTCPLMODE_F, RXPKTCPLMODE_F);

	sge->sge_control = csio_rd_reg32(hw, SGE_CONTROL_A);

	/* sge->csio_fl_align is set up by csio_wr_fixup_host_params(). */

	/*
	 * Set up to drop DOORBELL writes when the DOORBELL FIFO overflows
	 * and generate an interrupt when this occurs so we can recover.
	 */
	csio_set_reg_field(hw, SGE_DBFIFO_STATUS_A,
			   LP_INT_THRESH_T5_V(LP_INT_THRESH_T5_M),
			   LP_INT_THRESH_T5_V(CSIO_SGE_DBFIFO_INT_THRESH));
	csio_set_reg_field(hw, SGE_DBFIFO_STATUS2_A,
			   HP_INT_THRESH_T5_V(LP_INT_THRESH_T5_M),
			   HP_INT_THRESH_T5_V(CSIO_SGE_DBFIFO_INT_THRESH));

	csio_set_reg_field(hw, SGE_DOORBELL_CONTROL_A, ENABLE_DROP_F,
			   ENABLE_DROP_F);

	/* SGE_FL_BUFFER_SIZE0 is set up by csio_wr_fixup_host_params(). */

	CSIO_SET_FLBUF_SIZE(hw, 1, CSIO_SGE_FLBUF_SIZE1);
	csio_wr_reg32(hw, (CSIO_SGE_FLBUF_SIZE2 + sge->csio_fl_align - 1)
		      & ~(sge->csio_fl_align - 1), SGE_FL_BUFFER_SIZE2_A);
	csio_wr_reg32(hw, (CSIO_SGE_FLBUF_SIZE3 + sge->csio_fl_align - 1)
		      & ~(sge->csio_fl_align - 1), SGE_FL_BUFFER_SIZE3_A);
	CSIO_SET_FLBUF_SIZE(hw, 4, CSIO_SGE_FLBUF_SIZE4);
	CSIO_SET_FLBUF_SIZE(hw, 5, CSIO_SGE_FLBUF_SIZE5);
	CSIO_SET_FLBUF_SIZE(hw, 6, CSIO_SGE_FLBUF_SIZE6);
	CSIO_SET_FLBUF_SIZE(hw, 7, CSIO_SGE_FLBUF_SIZE7);
	CSIO_SET_FLBUF_SIZE(hw, 8, CSIO_SGE_FLBUF_SIZE8);

	for (i = 0; i < CSIO_SGE_FL_SIZE_REGS; i++)
		csio_get_flbuf_size(hw, sge, i);

	/* Initialize interrupt coalescing attributes */
	sge->timer_val[0] = CSIO_SGE_TIMER_VAL_0;
	sge->timer_val[1] = CSIO_SGE_TIMER_VAL_1;
	sge->timer_val[2] = CSIO_SGE_TIMER_VAL_2;
	sge->timer_val[3] = CSIO_SGE_TIMER_VAL_3;
	sge->timer_val[4] = CSIO_SGE_TIMER_VAL_4;
	sge->timer_val[5] = CSIO_SGE_TIMER_VAL_5;

	sge->counter_val[0] = CSIO_SGE_INT_CNT_VAL_0;
	sge->counter_val[1] = CSIO_SGE_INT_CNT_VAL_1;
	sge->counter_val[2] = CSIO_SGE_INT_CNT_VAL_2;
	sge->counter_val[3] = CSIO_SGE_INT_CNT_VAL_3;

	csio_wr_reg32(hw, THRESHOLD_0_V(sge->counter_val[0]) |
		      THRESHOLD_1_V(sge->counter_val[1]) |
		      THRESHOLD_2_V(sge->counter_val[2]) |
		      THRESHOLD_3_V(sge->counter_val[3]),
		      SGE_INGRESS_RX_THRESHOLD_A);

	csio_wr_reg32(hw,
		   TIMERVALUE0_V(csio_us_to_core_ticks(hw, sge->timer_val[0])) |
		   TIMERVALUE1_V(csio_us_to_core_ticks(hw, sge->timer_val[1])),
		   SGE_TIMER_VALUE_0_AND_1_A);

	csio_wr_reg32(hw,
		   TIMERVALUE2_V(csio_us_to_core_ticks(hw, sge->timer_val[2])) |
		   TIMERVALUE3_V(csio_us_to_core_ticks(hw, sge->timer_val[3])),
		   SGE_TIMER_VALUE_2_AND_3_A);

	csio_wr_reg32(hw,
		   TIMERVALUE4_V(csio_us_to_core_ticks(hw, sge->timer_val[4])) |
		   TIMERVALUE5_V(csio_us_to_core_ticks(hw, sge->timer_val[5])),
		   SGE_TIMER_VALUE_4_AND_5_A);

	csio_init_intr_coalesce_parms(hw);
}