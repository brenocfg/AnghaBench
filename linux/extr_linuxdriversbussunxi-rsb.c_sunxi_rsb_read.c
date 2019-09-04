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
typedef  int /*<<< orphan*/  u32 ;
struct sunxi_rsb {int /*<<< orphan*/  lock; scalar_t__ regs; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ RSB_ADDR ; 
 scalar_t__ RSB_CMD ; 
 int /*<<< orphan*/  RSB_CMD_RD16 ; 
 int /*<<< orphan*/  RSB_CMD_RD32 ; 
 int /*<<< orphan*/  RSB_CMD_RD8 ; 
 scalar_t__ RSB_DAR ; 
 int /*<<< orphan*/  RSB_DAR_RTA (int /*<<< orphan*/ ) ; 
 scalar_t__ RSB_DATA ; 
 int _sunxi_rsb_run_xfer (struct sunxi_rsb*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int sunxi_rsb_read(struct sunxi_rsb *rsb, u8 rtaddr, u8 addr,
			  u32 *buf, size_t len)
{
	u32 cmd;
	int ret;

	if (!buf)
		return -EINVAL;

	switch (len) {
	case 1:
		cmd = RSB_CMD_RD8;
		break;
	case 2:
		cmd = RSB_CMD_RD16;
		break;
	case 4:
		cmd = RSB_CMD_RD32;
		break;
	default:
		dev_err(rsb->dev, "Invalid access width: %zd\n", len);
		return -EINVAL;
	}

	mutex_lock(&rsb->lock);

	writel(addr, rsb->regs + RSB_ADDR);
	writel(RSB_DAR_RTA(rtaddr), rsb->regs + RSB_DAR);
	writel(cmd, rsb->regs + RSB_CMD);

	ret = _sunxi_rsb_run_xfer(rsb);
	if (ret)
		goto unlock;

	*buf = readl(rsb->regs + RSB_DATA);

unlock:
	mutex_unlock(&rsb->lock);

	return ret;
}