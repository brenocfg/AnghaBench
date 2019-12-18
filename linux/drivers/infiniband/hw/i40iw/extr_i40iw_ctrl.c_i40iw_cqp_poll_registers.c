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
struct i40iw_sc_cqp {TYPE_1__* dev; int /*<<< orphan*/  sq_ring; } ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;
struct TYPE_2__ {int /*<<< orphan*/ * cqp_cmd_stats; int /*<<< orphan*/  hw; scalar_t__ is_pf; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_PFPE_CQPERRCODES ; 
 int /*<<< orphan*/  I40E_VFPE_CQPERRCODES1 ; 
 int I40IW_ERR_CQP_COMPL_ERROR ; 
 int I40IW_ERR_TIMEOUT ; 
 int /*<<< orphan*/  I40IW_RING_MOVE_TAIL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I40IW_SLEEP_COUNT ; 
 size_t OP_COMPLETED_COMMANDS ; 
 int /*<<< orphan*/  i40iw_get_cqp_reg_info (struct i40iw_sc_cqp*,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 scalar_t__ i40iw_rd32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum i40iw_status_code i40iw_cqp_poll_registers(
						struct i40iw_sc_cqp *cqp,
						u32 tail,
						u32 count)
{
	u32 i = 0;
	u32 newtail, error, val;

	while (i < count) {
		i++;
		i40iw_get_cqp_reg_info(cqp, &val, &newtail, &error);
		if (error) {
			error = (cqp->dev->is_pf) ?
				 i40iw_rd32(cqp->dev->hw, I40E_PFPE_CQPERRCODES) :
				 i40iw_rd32(cqp->dev->hw, I40E_VFPE_CQPERRCODES1);
			return I40IW_ERR_CQP_COMPL_ERROR;
		}
		if (newtail != tail) {
			/* SUCCESS */
			I40IW_RING_MOVE_TAIL(cqp->sq_ring);
			cqp->dev->cqp_cmd_stats[OP_COMPLETED_COMMANDS]++;
			return 0;
		}
		udelay(I40IW_SLEEP_COUNT);
	}
	return I40IW_ERR_TIMEOUT;
}