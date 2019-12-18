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
struct igc_q_vector {int itr_val; scalar_t__ set_itr; int /*<<< orphan*/  itr_register; } ;

/* Variables and functions */
 int IGC_EITR_CNT_IGNR ; 
 int IGC_ITR_VAL_MASK ; 
 int IGC_QVECTOR_MASK ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void igc_write_itr(struct igc_q_vector *q_vector)
{
	u32 itr_val = q_vector->itr_val & IGC_QVECTOR_MASK;

	if (!q_vector->set_itr)
		return;

	if (!itr_val)
		itr_val = IGC_ITR_VAL_MASK;

	itr_val |= IGC_EITR_CNT_IGNR;

	writel(itr_val, q_vector->itr_register);
	q_vector->set_itr = 0;
}