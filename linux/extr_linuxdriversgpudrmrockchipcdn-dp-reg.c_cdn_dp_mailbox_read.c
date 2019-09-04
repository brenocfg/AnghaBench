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
struct cdn_dp_device {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ MAILBOX0_RD_DATA ; 
 scalar_t__ MAILBOX_EMPTY_ADDR ; 
 int /*<<< orphan*/  MAILBOX_RETRY_US ; 
 int /*<<< orphan*/  MAILBOX_TIMEOUT_US ; 
 int readl (scalar_t__) ; 
 int readx_poll_timeout (int (*) (scalar_t__),scalar_t__,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cdn_dp_mailbox_read(struct cdn_dp_device *dp)
{
	int val, ret;

	ret = readx_poll_timeout(readl, dp->regs + MAILBOX_EMPTY_ADDR,
				 val, !val, MAILBOX_RETRY_US,
				 MAILBOX_TIMEOUT_US);
	if (ret < 0)
		return ret;

	return readl(dp->regs + MAILBOX0_RD_DATA) & 0xff;
}