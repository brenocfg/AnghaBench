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
typedef  int /*<<< orphan*/  u32 ;
struct i40iw_sc_cqp {TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  hw; scalar_t__ is_pf; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_PFPE_CQPTAIL ; 
 int /*<<< orphan*/  I40E_PFPE_CQPTAIL_CQP_OP_ERR ; 
 int /*<<< orphan*/  I40E_PFPE_CQPTAIL_WQTAIL ; 
 int /*<<< orphan*/  I40E_VFPE_CQPTAIL1 ; 
 int /*<<< orphan*/  I40E_VFPE_CQPTAIL_CQP_OP_ERR ; 
 int /*<<< orphan*/  I40E_VFPE_CQPTAIL_WQTAIL ; 
 int /*<<< orphan*/  RS_32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40iw_rd32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void i40iw_get_cqp_reg_info(struct i40iw_sc_cqp *cqp,
					  u32 *val,
					  u32 *tail,
					  u32 *error)
{
	if (cqp->dev->is_pf) {
		*val = i40iw_rd32(cqp->dev->hw, I40E_PFPE_CQPTAIL);
		*tail = RS_32(*val, I40E_PFPE_CQPTAIL_WQTAIL);
		*error = RS_32(*val, I40E_PFPE_CQPTAIL_CQP_OP_ERR);
	} else {
		*val = i40iw_rd32(cqp->dev->hw, I40E_VFPE_CQPTAIL1);
		*tail = RS_32(*val, I40E_VFPE_CQPTAIL_WQTAIL);
		*error = RS_32(*val, I40E_VFPE_CQPTAIL_CQP_OP_ERR);
	}
}