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
struct TYPE_2__ {int /*<<< orphan*/  tickcnt; } ;
struct brcmf_sdio {int /*<<< orphan*/  watchdog_wait; TYPE_1__ sdcnt; int /*<<< orphan*/  sdiodev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  allow_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_sdio_bus_watchdog (struct brcmf_sdio*) ; 
 int /*<<< orphan*/  brcmf_sdiod_freezer_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_sdiod_freezer_uncount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_sdiod_try_freeze (int /*<<< orphan*/ ) ; 
 scalar_t__ kthread_should_stop () ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int wait_for_completion_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
brcmf_sdio_watchdog_thread(void *data)
{
	struct brcmf_sdio *bus = (struct brcmf_sdio *)data;
	int wait;

	allow_signal(SIGTERM);
	/* Run until signal received */
	brcmf_sdiod_freezer_count(bus->sdiodev);
	while (1) {
		if (kthread_should_stop())
			break;
		brcmf_sdiod_freezer_uncount(bus->sdiodev);
		wait = wait_for_completion_interruptible(&bus->watchdog_wait);
		brcmf_sdiod_freezer_count(bus->sdiodev);
		brcmf_sdiod_try_freeze(bus->sdiodev);
		if (!wait) {
			brcmf_sdio_bus_watchdog(bus);
			/* Count the tick for reference */
			bus->sdcnt.tickcnt++;
			reinit_completion(&bus->watchdog_wait);
		} else
			break;
	}
	return 0;
}