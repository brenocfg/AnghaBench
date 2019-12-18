#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct iavf_vsi {TYPE_3__* back; } ;
struct TYPE_5__ {TYPE_1__* ring; } ;
struct iavf_q_vector {int arm_wb_state; int /*<<< orphan*/  reg_idx; TYPE_2__ tx; } ;
struct TYPE_6__ {int /*<<< orphan*/  hw; } ;
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 int IAVF_TXR_FLAGS_WB_ON_ITR ; 
 int /*<<< orphan*/  IAVF_VFINT_DYN_CTLN1 (int /*<<< orphan*/ ) ; 
 int IAVF_VFINT_DYN_CTLN1_ITR_INDX_MASK ; 
 int IAVF_VFINT_DYN_CTLN1_WB_ON_ITR_MASK ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void iavf_enable_wb_on_itr(struct iavf_vsi *vsi,
				  struct iavf_q_vector *q_vector)
{
	u16 flags = q_vector->tx.ring[0].flags;
	u32 val;

	if (!(flags & IAVF_TXR_FLAGS_WB_ON_ITR))
		return;

	if (q_vector->arm_wb_state)
		return;

	val = IAVF_VFINT_DYN_CTLN1_WB_ON_ITR_MASK |
	      IAVF_VFINT_DYN_CTLN1_ITR_INDX_MASK; /* set noitr */

	wr32(&vsi->back->hw,
	     IAVF_VFINT_DYN_CTLN1(q_vector->reg_idx), val);
	q_vector->arm_wb_state = true;
}