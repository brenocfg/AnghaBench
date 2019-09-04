#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tifm_ms {int /*<<< orphan*/  cmd_flags; TYPE_1__* req; } ;
struct tifm_dev {int /*<<< orphan*/  lock; scalar_t__ addr; int /*<<< orphan*/  dev; } ;
struct memstick_host {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  error; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_INT ; 
 int /*<<< orphan*/  CMD_READY ; 
 int /*<<< orphan*/  EILSEQ ; 
 int /*<<< orphan*/  ETIME ; 
 scalar_t__ SOCK_MS_STATUS ; 
 scalar_t__ SOCK_MS_SYSTEM ; 
 unsigned int TIFM_MS_STAT_CRC ; 
 unsigned int TIFM_MS_STAT_MSINT ; 
 unsigned int TIFM_MS_STAT_RDY ; 
 unsigned int TIFM_MS_STAT_TOE ; 
 unsigned int TIFM_MS_SYS_INTCLR ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned int,int /*<<< orphan*/ ) ; 
 struct tifm_ms* memstick_priv (struct memstick_host*) ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ tifm_get_drvdata (struct tifm_dev*) ; 
 int tifm_ms_check_status (struct tifm_ms*) ; 
 int /*<<< orphan*/  tifm_ms_complete_cmd (struct tifm_ms*) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static void tifm_ms_card_event(struct tifm_dev *sock)
{
	struct tifm_ms *host;
	unsigned int host_status = 0;
	int rc = 1;

	spin_lock(&sock->lock);
	host = memstick_priv((struct memstick_host *)tifm_get_drvdata(sock));
	host_status = readl(sock->addr + SOCK_MS_STATUS);
	dev_dbg(&sock->dev, "host event: host_status %x, flags %x\n",
		host_status, host->cmd_flags);

	if (host->req) {
		if (host_status & TIFM_MS_STAT_TOE)
			host->req->error = -ETIME;
		else if (host_status & TIFM_MS_STAT_CRC)
			host->req->error = -EILSEQ;

		if (host_status & TIFM_MS_STAT_RDY)
			host->cmd_flags |= CMD_READY;

		if (host_status & TIFM_MS_STAT_MSINT)
			host->cmd_flags |= CARD_INT;

		rc = tifm_ms_check_status(host);

	}

	writel(TIFM_MS_SYS_INTCLR | readl(sock->addr + SOCK_MS_SYSTEM),
	       sock->addr + SOCK_MS_SYSTEM);

	if (!rc)
		tifm_ms_complete_cmd(host);

	spin_unlock(&sock->lock);
	return;
}