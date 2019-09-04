#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct timeval {int tv_sec; int tv_usec; } ;
struct mmc_command {int opcode; int arg; int flags; int busy_timeout; TYPE_4__* data; int /*<<< orphan*/  error; } ;
struct TYPE_5__ {int tv_sec; int tv_usec; } ;
struct bcm2835_host {int max_delay; int use_busy; int delay_after_this_stop; int delay_after_stop; int sectors; TYPE_3__* mrq; int /*<<< orphan*/  use_sbc; TYPE_1__ stop_time; int /*<<< orphan*/  finish_tasklet; int /*<<< orphan*/  mmc; struct mmc_command* cmd; int /*<<< orphan*/  timer; scalar_t__ debug; } ;
struct TYPE_8__ {int flags; int blocks; int blksz; } ;
struct TYPE_7__ {TYPE_2__* cmd; } ;
struct TYPE_6__ {int arg; } ;

/* Variables and functions */
 unsigned long DIV_ROUND_UP (int,int) ; 
 int /*<<< orphan*/  EILSEQ ; 
 int /*<<< orphan*/  EINVAL ; 
 unsigned long HZ ; 
 int MMC_DATA_READ ; 
 int MMC_DATA_WRITE ; 
 int MMC_RSP_136 ; 
 int MMC_RSP_BUSY ; 
 int MMC_RSP_PRESENT ; 
 int /*<<< orphan*/  SDARG ; 
 int /*<<< orphan*/  SDCMD ; 
 int SDCMD_BUSYWAIT ; 
 int SDCMD_CMD_MASK ; 
 int SDCMD_LONG_RESPONSE ; 
 int SDCMD_NEW_FLAG ; 
 int SDCMD_NO_RESPONSE ; 
 int SDCMD_READ_CMD ; 
 int SDCMD_WRITE_CMD ; 
 int /*<<< orphan*/  SDHSTS ; 
 int SDHSTS_ERROR_MASK ; 
 int /*<<< orphan*/  WARN_ON (struct mmc_command*) ; 
 int /*<<< orphan*/  bcm2835_sdhost_dumpregs (struct bcm2835_host*) ; 
 int /*<<< orphan*/  bcm2835_sdhost_prepare_data (struct bcm2835_host*,struct mmc_command*) ; 
 int bcm2835_sdhost_read (struct bcm2835_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm2835_sdhost_write (struct bcm2835_host*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_gettimeofday (struct timeval*) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  log_event (char*,int,int) ; 
 int max (unsigned int,int) ; 
 int /*<<< orphan*/  mmc_hostname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int,int,int,...) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warning (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 

bool bcm2835_sdhost_send_command(struct bcm2835_host *host,
				 struct mmc_command *cmd)
{
	u32 sdcmd, sdhsts;
	unsigned long timeout;
	int delay;

	WARN_ON(host->cmd);
	log_event("CMD<", cmd->opcode, cmd->arg);

	if (cmd->data)
		pr_debug("%s: send_command %d 0x%x "
			 "(flags 0x%x) - %s %d*%d\n",
			 mmc_hostname(host->mmc),
			 cmd->opcode, cmd->arg, cmd->flags,
			 (cmd->data->flags & MMC_DATA_READ) ?
			 "read" : "write", cmd->data->blocks,
			 cmd->data->blksz);
	else
		pr_debug("%s: send_command %d 0x%x (flags 0x%x)\n",
			 mmc_hostname(host->mmc),
			 cmd->opcode, cmd->arg, cmd->flags);

	/* Wait max 100 ms */
	timeout = 10000;

	while (bcm2835_sdhost_read(host, SDCMD) & SDCMD_NEW_FLAG) {
		if (timeout == 0) {
			pr_warn("%s: previous command never completed.\n",
				mmc_hostname(host->mmc));
			if (host->debug)
				bcm2835_sdhost_dumpregs(host);
			cmd->error = -EILSEQ;
			tasklet_schedule(&host->finish_tasklet);
			return false;
		}
		timeout--;
		udelay(10);
	}

	delay = (10000 - timeout)/100;
	if (delay > host->max_delay) {
		host->max_delay = delay;
		pr_warning("%s: controller hung for %d ms\n",
			   mmc_hostname(host->mmc),
			   host->max_delay);
	}

	timeout = jiffies;
	if (!cmd->data && cmd->busy_timeout > 9000)
		timeout += DIV_ROUND_UP(cmd->busy_timeout, 1000) * HZ + HZ;
	else
		timeout += 10 * HZ;
	mod_timer(&host->timer, timeout);

	host->cmd = cmd;

	/* Clear any error flags */
	sdhsts = bcm2835_sdhost_read(host, SDHSTS);
	if (sdhsts & SDHSTS_ERROR_MASK)
		bcm2835_sdhost_write(host, sdhsts, SDHSTS);

	if ((cmd->flags & MMC_RSP_136) && (cmd->flags & MMC_RSP_BUSY)) {
		pr_err("%s: unsupported response type!\n",
			mmc_hostname(host->mmc));
		cmd->error = -EINVAL;
		tasklet_schedule(&host->finish_tasklet);
		return false;
	}

	bcm2835_sdhost_prepare_data(host, cmd);

	bcm2835_sdhost_write(host, cmd->arg, SDARG);

	sdcmd = cmd->opcode & SDCMD_CMD_MASK;

	host->use_busy = 0;
	if (!(cmd->flags & MMC_RSP_PRESENT)) {
		sdcmd |= SDCMD_NO_RESPONSE;
	} else {
		if (cmd->flags & MMC_RSP_136)
			sdcmd |= SDCMD_LONG_RESPONSE;
		if (cmd->flags & MMC_RSP_BUSY) {
			sdcmd |= SDCMD_BUSYWAIT;
			host->use_busy = 1;
		}
	}

	if (cmd->data) {
		log_event("CMDD", cmd->data->blocks, cmd->data->blksz);
		if (host->delay_after_this_stop) {
			struct timeval now;
			int time_since_stop;
			do_gettimeofday(&now);
			time_since_stop = (now.tv_sec - host->stop_time.tv_sec);
			if (time_since_stop < 2) {
				/* Possibly less than one second */
				time_since_stop = time_since_stop * 1000000 +
					(now.tv_usec - host->stop_time.tv_usec);
				if (time_since_stop <
				    host->delay_after_this_stop)
					udelay(host->delay_after_this_stop -
					       time_since_stop);
			}
		}

		host->delay_after_this_stop = host->delay_after_stop;
		if ((cmd->data->flags & MMC_DATA_READ) && !host->use_sbc) {
			/* See if read crosses one of the hazardous sectors */
			u32 first_blk, last_blk;

			/* Intentionally include the following sector because
			   without CMD23/SBC the read may run on. */
			first_blk = host->mrq->cmd->arg;
			last_blk = first_blk + cmd->data->blocks;

			if (((last_blk >= (host->sectors - 64)) &&
			     (first_blk <= (host->sectors - 64))) ||
			    ((last_blk >= (host->sectors - 32)) &&
			     (first_blk <= (host->sectors - 32)))) {
				host->delay_after_this_stop =
					max(250u, host->delay_after_stop);
			}
		}

		if (cmd->data->flags & MMC_DATA_WRITE)
			sdcmd |= SDCMD_WRITE_CMD;
		if (cmd->data->flags & MMC_DATA_READ)
			sdcmd |= SDCMD_READ_CMD;
	}

	bcm2835_sdhost_write(host, sdcmd | SDCMD_NEW_FLAG, SDCMD);

	return true;
}