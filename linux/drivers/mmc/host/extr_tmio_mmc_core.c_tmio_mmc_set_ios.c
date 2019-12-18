#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct tmio_mmc_host {int /*<<< orphan*/  ios_lock; int /*<<< orphan*/  clk_cache; TYPE_5__* mrq; TYPE_2__* pdev; int /*<<< orphan*/  (* set_clock ) (struct tmio_mmc_host*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  lock; int /*<<< orphan*/  last_req_ts; } ;
struct mmc_ios {int power_mode; int /*<<< orphan*/  clock; int /*<<< orphan*/  bus_width; int /*<<< orphan*/  vdd; } ;
struct mmc_host {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_10__ {TYPE_1__* cmd; } ;
struct TYPE_9__ {int /*<<< orphan*/  comm; } ;
struct TYPE_8__ {struct device dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  opcode; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  EINTR ; 
 void* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (TYPE_5__*) ; 
#define  MMC_POWER_OFF 130 
#define  MMC_POWER_ON 129 
#define  MMC_POWER_UP 128 
 int /*<<< orphan*/  PTR_ERR (TYPE_5__*) ; 
 TYPE_3__* current ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  jiffies ; 
 struct tmio_mmc_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct tmio_mmc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct tmio_mmc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct tmio_mmc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_pid_nr (TYPE_3__*) ; 
 int /*<<< orphan*/  tmio_mmc_power_off (struct tmio_mmc_host*) ; 
 int /*<<< orphan*/  tmio_mmc_power_on (struct tmio_mmc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tmio_mmc_set_bus_width (struct tmio_mmc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void tmio_mmc_set_ios(struct mmc_host *mmc, struct mmc_ios *ios)
{
	struct tmio_mmc_host *host = mmc_priv(mmc);
	struct device *dev = &host->pdev->dev;
	unsigned long flags;

	mutex_lock(&host->ios_lock);

	spin_lock_irqsave(&host->lock, flags);
	if (host->mrq) {
		if (IS_ERR(host->mrq)) {
			dev_dbg(dev,
				"%s.%d: concurrent .set_ios(), clk %u, mode %u\n",
				current->comm, task_pid_nr(current),
				ios->clock, ios->power_mode);
			host->mrq = ERR_PTR(-EINTR);
		} else {
			dev_dbg(dev,
				"%s.%d: CMD%u active since %lu, now %lu!\n",
				current->comm, task_pid_nr(current),
				host->mrq->cmd->opcode, host->last_req_ts,
				jiffies);
		}
		spin_unlock_irqrestore(&host->lock, flags);

		mutex_unlock(&host->ios_lock);
		return;
	}

	host->mrq = ERR_PTR(-EBUSY);

	spin_unlock_irqrestore(&host->lock, flags);

	switch (ios->power_mode) {
	case MMC_POWER_OFF:
		tmio_mmc_power_off(host);
		host->set_clock(host, 0);
		break;
	case MMC_POWER_UP:
		tmio_mmc_power_on(host, ios->vdd);
		host->set_clock(host, ios->clock);
		tmio_mmc_set_bus_width(host, ios->bus_width);
		break;
	case MMC_POWER_ON:
		host->set_clock(host, ios->clock);
		tmio_mmc_set_bus_width(host, ios->bus_width);
		break;
	}

	/* Let things settle. delay taken from winCE driver */
	usleep_range(140, 200);
	if (PTR_ERR(host->mrq) == -EINTR)
		dev_dbg(&host->pdev->dev,
			"%s.%d: IOS interrupted: clk %u, mode %u",
			current->comm, task_pid_nr(current),
			ios->clock, ios->power_mode);
	host->mrq = NULL;

	host->clk_cache = ios->clock;

	mutex_unlock(&host->ios_lock);
}