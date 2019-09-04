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
typedef  int u8 ;
typedef  int u64 ;
typedef  int u16 ;
struct TYPE_4__ {int /*<<< orphan*/  cq_id; int /*<<< orphan*/  shadow_area; } ;
struct i40iw_sc_cq {TYPE_2__ cq_uk; TYPE_1__* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  hw; scalar_t__ is_pf; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_PFPE_CQARM ; 
 int /*<<< orphan*/  I40E_VFPE_CQARM1 ; 
 int /*<<< orphan*/  I40IW_CQ_DBSA_ARM_NEXT ; 
 int /*<<< orphan*/  I40IW_CQ_DBSA_ARM_NEXT_SE ; 
 int /*<<< orphan*/  I40IW_CQ_DBSA_ARM_SEQ_NUM ; 
 int /*<<< orphan*/  I40IW_CQ_DBSA_SW_CQ_SELECT ; 
 int LS_64 (int,int /*<<< orphan*/ ) ; 
 scalar_t__ RS_64 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_64bit_val (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  i40iw_wr32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_64bit_val (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void i40iw_sc_ccq_arm(struct i40iw_sc_cq *ccq)
{
	u64 temp_val;
	u16 sw_cq_sel;
	u8 arm_next_se;
	u8 arm_seq_num;

	/* write to cq doorbell shadow area */
	/* arm next se should always be zero */
	get_64bit_val(ccq->cq_uk.shadow_area, 32, &temp_val);

	sw_cq_sel = (u16)RS_64(temp_val, I40IW_CQ_DBSA_SW_CQ_SELECT);
	arm_next_se = (u8)RS_64(temp_val, I40IW_CQ_DBSA_ARM_NEXT_SE);

	arm_seq_num = (u8)RS_64(temp_val, I40IW_CQ_DBSA_ARM_SEQ_NUM);
	arm_seq_num++;

	temp_val = LS_64(arm_seq_num, I40IW_CQ_DBSA_ARM_SEQ_NUM) |
		   LS_64(sw_cq_sel, I40IW_CQ_DBSA_SW_CQ_SELECT) |
		   LS_64(arm_next_se, I40IW_CQ_DBSA_ARM_NEXT_SE) |
		   LS_64(1, I40IW_CQ_DBSA_ARM_NEXT);

	set_64bit_val(ccq->cq_uk.shadow_area, 32, temp_val);

	wmb();       /* make sure shadow area is updated before arming */

	if (ccq->dev->is_pf)
		i40iw_wr32(ccq->dev->hw, I40E_PFPE_CQARM, ccq->cq_uk.cq_id);
	else
		i40iw_wr32(ccq->dev->hw, I40E_VFPE_CQARM1, ccq->cq_uk.cq_id);
}