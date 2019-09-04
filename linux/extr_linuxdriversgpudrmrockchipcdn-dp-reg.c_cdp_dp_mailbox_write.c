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
typedef  int /*<<< orphan*/  u8 ;
struct cdn_dp_device {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ MAILBOX0_WR_DATA ; 
 scalar_t__ MAILBOX_FULL_ADDR ; 
 int /*<<< orphan*/  MAILBOX_RETRY_US ; 
 int /*<<< orphan*/  MAILBOX_TIMEOUT_US ; 
 int /*<<< orphan*/  readl ; 
 int readx_poll_timeout (int /*<<< orphan*/ ,scalar_t__,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int cdp_dp_mailbox_write(struct cdn_dp_device *dp, u8 val)
{
	int ret, full;

	ret = readx_poll_timeout(readl, dp->regs + MAILBOX_FULL_ADDR,
				 full, !full, MAILBOX_RETRY_US,
				 MAILBOX_TIMEOUT_US);
	if (ret < 0)
		return ret;

	writel(val, dp->regs + MAILBOX0_WR_DATA);

	return 0;
}