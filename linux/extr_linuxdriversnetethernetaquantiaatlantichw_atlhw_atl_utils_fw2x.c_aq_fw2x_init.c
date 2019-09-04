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
struct aq_hw_s {unsigned int mbox_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AQ_HW_WAIT_FOR (int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  HW_ATL_FW2X_MPI_MBOX_ADDR ; 
 unsigned int aq_hw_read_reg (struct aq_hw_s*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int aq_fw2x_init(struct aq_hw_s *self)
{
	int err = 0;

	/* check 10 times by 1ms */
	AQ_HW_WAIT_FOR(0U != (self->mbox_addr =
			aq_hw_read_reg(self, HW_ATL_FW2X_MPI_MBOX_ADDR)),
		       1000U, 10U);
	return err;
}