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
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct bnxt_qplib_rcfw {int cmdq_depth; int /*<<< orphan*/  cmdq_bitmap; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 scalar_t__ RCFW_BLOCKED_CMD_WAIT_COUNT ; 
 int /*<<< orphan*/  bnxt_qplib_service_creq (unsigned long) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __block_for_resp(struct bnxt_qplib_rcfw *rcfw, u16 cookie)
{
	u32 count = RCFW_BLOCKED_CMD_WAIT_COUNT;
	u16 cbit;

	cbit = cookie % rcfw->cmdq_depth;
	if (!test_bit(cbit, rcfw->cmdq_bitmap))
		goto done;
	do {
		mdelay(1); /* 1m sec */
		bnxt_qplib_service_creq((unsigned long)rcfw);
	} while (test_bit(cbit, rcfw->cmdq_bitmap) && --count);
done:
	return count ? 0 : -ETIMEDOUT;
}