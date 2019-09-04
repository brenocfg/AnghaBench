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
typedef  int u8 ;
typedef  int u16 ;
struct cq_desc {int type_color; int /*<<< orphan*/  completed_index; int /*<<< orphan*/  q_number; } ;

/* Variables and functions */
 int const CQ_DESC_COLOR_MASK ; 
 int const CQ_DESC_COLOR_SHIFT ; 
 int CQ_DESC_COMP_NDX_MASK ; 
 int CQ_DESC_Q_NUM_MASK ; 
 int const CQ_DESC_TYPE_MASK ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rmb () ; 

__attribute__((used)) static inline void cq_desc_dec(const struct cq_desc *desc_arg,
	u8 *type, u8 *color, u16 *q_number, u16 *completed_index)
{
	const struct cq_desc *desc = desc_arg;
	const u8 type_color = desc->type_color;

	*color = (type_color >> CQ_DESC_COLOR_SHIFT) & CQ_DESC_COLOR_MASK;

	/*
	 * Make sure color bit is read from desc *before* other fields
	 * are read from desc.  Hardware guarantees color bit is last
	 * bit (byte) written.  Adding the rmb() prevents the compiler
	 * and/or CPU from reordering the reads which would potentially
	 * result in reading stale values.
	 */

	rmb();

	*type = type_color & CQ_DESC_TYPE_MASK;
	*q_number = le16_to_cpu(desc->q_number) & CQ_DESC_Q_NUM_MASK;
	*completed_index = le16_to_cpu(desc->completed_index) &
		CQ_DESC_COMP_NDX_MASK;
}