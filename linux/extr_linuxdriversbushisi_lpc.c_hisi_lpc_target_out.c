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
typedef  unsigned long u32 ;
struct lpc_cycle_para {int opflags; } ;
struct hisi_lpc_dev {int /*<<< orphan*/  cycle_lock; scalar_t__ membase; } ;

/* Variables and functions */
 int EINVAL ; 
 int FG_INCRADDR_LPC ; 
 unsigned int LPC_MAX_WAITCNT ; 
 unsigned int LPC_PEROP_WAITCNT ; 
 scalar_t__ LPC_REG_ADDR ; 
 scalar_t__ LPC_REG_CMD ; 
 unsigned long LPC_REG_CMD_OP ; 
 unsigned long LPC_REG_CMD_SAMEADDR ; 
 scalar_t__ LPC_REG_OP_LEN ; 
 scalar_t__ LPC_REG_STARTUP_SIGNAL ; 
 int /*<<< orphan*/  LPC_REG_STARTUP_SIGNAL_START ; 
 scalar_t__ LPC_REG_WDATA ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int wait_lpc_idle (scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  writesb (scalar_t__,unsigned char const*,unsigned long) ; 

__attribute__((used)) static int hisi_lpc_target_out(struct hisi_lpc_dev *lpcdev,
			       struct lpc_cycle_para *para, unsigned long addr,
			       const unsigned char *buf, unsigned long opcnt)
{
	unsigned int waitcnt;
	unsigned long flags;
	u32 cmd_word;
	int ret;

	if (!buf || !opcnt || !para || !lpcdev)
		return -EINVAL;

	/* default is increasing address */
	cmd_word = LPC_REG_CMD_OP; /* IO mode, write */
	waitcnt = LPC_PEROP_WAITCNT;
	if (!(para->opflags & FG_INCRADDR_LPC)) {
		cmd_word |= LPC_REG_CMD_SAMEADDR;
		waitcnt = LPC_MAX_WAITCNT;
	}

	spin_lock_irqsave(&lpcdev->cycle_lock, flags);

	writel_relaxed(opcnt, lpcdev->membase + LPC_REG_OP_LEN);
	writel_relaxed(cmd_word, lpcdev->membase + LPC_REG_CMD);
	writel_relaxed(addr, lpcdev->membase + LPC_REG_ADDR);

	writesb(lpcdev->membase + LPC_REG_WDATA, buf, opcnt);

	writel(LPC_REG_STARTUP_SIGNAL_START,
	       lpcdev->membase + LPC_REG_STARTUP_SIGNAL);

	/* whether the operation is finished */
	ret = wait_lpc_idle(lpcdev->membase, waitcnt);

	spin_unlock_irqrestore(&lpcdev->cycle_lock, flags);

	return ret;
}