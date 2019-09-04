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
struct vexpress_syscfg_func {int num_templates; int* template; struct vexpress_syscfg* syscfg; } ;
struct vexpress_syscfg {int /*<<< orphan*/  dev; scalar_t__ base; } ;

/* Variables and functions */
 int EBUSY ; 
 int EFAULT ; 
 int EINTR ; 
 int EINVAL ; 
 int ETIMEDOUT ; 
 scalar_t__ SYS_CFGCTRL ; 
 int SYS_CFGCTRL_START ; 
 int SYS_CFGCTRL_WRITE ; 
 scalar_t__ SYS_CFGDATA ; 
 scalar_t__ SYS_CFGSTAT ; 
 int SYS_CFGSTAT_COMPLETE ; 
 int SYS_CFGSTAT_ERR ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,struct vexpress_syscfg_func*,int,...) ; 
 int /*<<< orphan*/  irqs_disabled () ; 
 int /*<<< orphan*/  mb () ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  schedule_timeout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (long) ; 
 int /*<<< orphan*/  usecs_to_jiffies (long) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int vexpress_syscfg_exec(struct vexpress_syscfg_func *func,
		int index, bool write, u32 *data)
{
	struct vexpress_syscfg *syscfg = func->syscfg;
	u32 command, status;
	int tries;
	long timeout;

	if (WARN_ON(index >= func->num_templates))
		return -EINVAL;

	command = readl(syscfg->base + SYS_CFGCTRL);
	if (WARN_ON(command & SYS_CFGCTRL_START))
		return -EBUSY;

	command = func->template[index];
	command |= SYS_CFGCTRL_START;
	command |= write ? SYS_CFGCTRL_WRITE : 0;

	/* Use a canary for reads */
	if (!write)
		*data = 0xdeadbeef;

	dev_dbg(syscfg->dev, "func %p, command %x, data %x\n",
			func, command, *data);
	writel(*data, syscfg->base + SYS_CFGDATA);
	writel(0, syscfg->base + SYS_CFGSTAT);
	writel(command, syscfg->base + SYS_CFGCTRL);
	mb();

	/* The operation can take ages... Go to sleep, 100us initially */
	tries = 100;
	timeout = 100;
	do {
		if (!irqs_disabled()) {
			set_current_state(TASK_INTERRUPTIBLE);
			schedule_timeout(usecs_to_jiffies(timeout));
			if (signal_pending(current))
				return -EINTR;
		} else {
			udelay(timeout);
		}

		status = readl(syscfg->base + SYS_CFGSTAT);
		if (status & SYS_CFGSTAT_ERR)
			return -EFAULT;

		if (timeout > 20)
			timeout -= 20;
	} while (--tries && !(status & SYS_CFGSTAT_COMPLETE));
	if (WARN_ON_ONCE(!tries))
		return -ETIMEDOUT;

	if (!write) {
		*data = readl(syscfg->base + SYS_CFGDATA);
		dev_dbg(syscfg->dev, "func %p, read data %x\n", func, *data);
	}

	return 0;
}