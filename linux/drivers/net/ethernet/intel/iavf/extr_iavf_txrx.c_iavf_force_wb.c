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
typedef  int u32 ;
struct iavf_vsi {TYPE_1__* back; } ;
struct iavf_q_vector {int /*<<< orphan*/  reg_idx; } ;
struct TYPE_2__ {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  IAVF_VFINT_DYN_CTLN1 (int /*<<< orphan*/ ) ; 
 int IAVF_VFINT_DYN_CTLN1_INTENA_MASK ; 
 int IAVF_VFINT_DYN_CTLN1_ITR_INDX_MASK ; 
 int IAVF_VFINT_DYN_CTLN1_SWINT_TRIG_MASK ; 
 int IAVF_VFINT_DYN_CTLN1_SW_ITR_INDX_ENA_MASK ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void iavf_force_wb(struct iavf_vsi *vsi, struct iavf_q_vector *q_vector)
{
	u32 val = IAVF_VFINT_DYN_CTLN1_INTENA_MASK |
		  IAVF_VFINT_DYN_CTLN1_ITR_INDX_MASK | /* set noitr */
		  IAVF_VFINT_DYN_CTLN1_SWINT_TRIG_MASK |
		  IAVF_VFINT_DYN_CTLN1_SW_ITR_INDX_ENA_MASK
		  /* allow 00 to be written to the index */;

	wr32(&vsi->back->hw,
	     IAVF_VFINT_DYN_CTLN1(q_vector->reg_idx),
	     val);
}