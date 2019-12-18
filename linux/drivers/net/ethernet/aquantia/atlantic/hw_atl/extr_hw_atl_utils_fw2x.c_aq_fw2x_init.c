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
struct aq_hw_s {unsigned int mbox_addr; unsigned int rpc_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  aq_fw2x_mbox_get ; 
 int /*<<< orphan*/  aq_fw2x_rpc_get ; 
 int readx_poll_timeout_atomic (int /*<<< orphan*/ ,struct aq_hw_s*,unsigned int,int,unsigned int,unsigned int) ; 

__attribute__((used)) static int aq_fw2x_init(struct aq_hw_s *self)
{
	int err = 0;

	/* check 10 times by 1ms */
	err = readx_poll_timeout_atomic(aq_fw2x_mbox_get,
					self, self->mbox_addr,
					self->mbox_addr != 0U,
					1000U, 10000U);

	err = readx_poll_timeout_atomic(aq_fw2x_rpc_get,
					self, self->rpc_addr,
					self->rpc_addr != 0U,
					1000U, 100000U);

	return err;
}