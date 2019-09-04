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
typedef  int u16 ;
struct TYPE_2__ {scalar_t__ db; } ;
struct ocrdma_dev {TYPE_1__ nic_info; } ;

/* Variables and functions */
 scalar_t__ OCRDMA_DB_EQ_OFFSET ; 
 int OCRDMA_EQ_CLR_SHIFT ; 
 int OCRDMA_EQ_ID_EXT_MASK ; 
 int OCRDMA_EQ_ID_EXT_MASK_SHIFT ; 
 int OCRDMA_EQ_ID_MASK ; 
 int OCRDMA_EQ_TYPE_SHIFT ; 
 int OCRDMA_NUM_EQE_SHIFT ; 
 int OCRDMA_REARM_SHIFT ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 

__attribute__((used)) static void ocrdma_ring_eq_db(struct ocrdma_dev *dev, u16 eq_id,
			      bool arm, bool clear_int, u16 num_eqe)
{
	u32 val = 0;

	val |= eq_id & OCRDMA_EQ_ID_MASK;
	val |= ((eq_id & OCRDMA_EQ_ID_EXT_MASK) << OCRDMA_EQ_ID_EXT_MASK_SHIFT);
	if (arm)
		val |= (1 << OCRDMA_REARM_SHIFT);
	if (clear_int)
		val |= (1 << OCRDMA_EQ_CLR_SHIFT);
	val |= (1 << OCRDMA_EQ_TYPE_SHIFT);
	val |= (num_eqe << OCRDMA_NUM_EQE_SHIFT);
	iowrite32(val, dev->nic_info.db + OCRDMA_DB_EQ_OFFSET);
}