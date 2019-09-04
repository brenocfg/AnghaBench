#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct bcm2835_host {TYPE_2__* mrq; int /*<<< orphan*/  mmc; } ;
struct TYPE_4__ {TYPE_1__* data; } ;
struct TYPE_3__ {int flags; int /*<<< orphan*/  error; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETIMEDOUT ; 
 int MMC_DATA_READ ; 
 int /*<<< orphan*/  SDEDM ; 
 scalar_t__ SDEDM_FORCE_DATA_MODE ; 
 scalar_t__ SDEDM_FSM_DATAMODE ; 
 scalar_t__ SDEDM_FSM_IDENTMODE ; 
 scalar_t__ SDEDM_FSM_MASK ; 
 scalar_t__ SDEDM_FSM_READWAIT ; 
 scalar_t__ SDEDM_FSM_WRITESTART1 ; 
 int /*<<< orphan*/  bcm2835_sdhost_dumpregs (struct bcm2835_host*) ; 
 scalar_t__ bcm2835_sdhost_read (struct bcm2835_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm2835_sdhost_write (struct bcm2835_host*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  log_dump () ; 
 int /*<<< orphan*/  log_event (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_hostname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void bcm2835_sdhost_wait_transfer_complete(struct bcm2835_host *host)
{
	int timediff;
	u32 alternate_idle;
	u32 edm;

	alternate_idle = (host->mrq->data->flags & MMC_DATA_READ) ?
		SDEDM_FSM_READWAIT : SDEDM_FSM_WRITESTART1;

	edm = bcm2835_sdhost_read(host, SDEDM);

	log_event("WTC<", edm, 0);

	timediff = 0;

	while (1) {
		u32 fsm = edm & SDEDM_FSM_MASK;
		if ((fsm == SDEDM_FSM_IDENTMODE) ||
		    (fsm == SDEDM_FSM_DATAMODE))
			break;
		if (fsm == alternate_idle) {
			bcm2835_sdhost_write(host,
					     edm | SDEDM_FORCE_DATA_MODE,
					     SDEDM);
			break;
		}

		timediff++;
		if (timediff == 100000) {
			pr_err("%s: wait_transfer_complete - still waiting after %d retries\n",
			       mmc_hostname(host->mmc),
			       timediff);
			log_dump();
			bcm2835_sdhost_dumpregs(host);
			host->mrq->data->error = -ETIMEDOUT;
			log_event("WTC!", edm, 0);
			return;
		}
		cpu_relax();
		edm = bcm2835_sdhost_read(host, SDEDM);
	}
	log_event("WTC>", edm, 0);
}