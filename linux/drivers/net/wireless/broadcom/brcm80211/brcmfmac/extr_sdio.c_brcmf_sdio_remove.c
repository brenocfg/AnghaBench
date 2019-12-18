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
struct brcmf_sdio {struct brcmf_sdio* hdrbuf; struct brcmf_sdio* rxbuf; TYPE_1__* sdiodev; scalar_t__ ci; scalar_t__ brcmf_wq; int /*<<< orphan*/  datawork; int /*<<< orphan*/ * watchdog_tsk; } ;
struct TYPE_2__ {scalar_t__ state; scalar_t__ settings; int /*<<< orphan*/  func1; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ BRCMF_SDIOD_NOMEDIUM ; 
 int /*<<< orphan*/  CLK_AVAIL ; 
 int /*<<< orphan*/  CLK_NONE ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  brcmf_chip_detach (scalar_t__) ; 
 int /*<<< orphan*/  brcmf_chip_set_passive (scalar_t__) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  brcmf_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_release_module_param (scalar_t__) ; 
 int /*<<< orphan*/  brcmf_sdio_clkctl (struct brcmf_sdio*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  brcmf_sdio_wd_timer (struct brcmf_sdio*,int) ; 
 int /*<<< orphan*/  brcmf_sdiod_intr_unregister (TYPE_1__*) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_workqueue (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct brcmf_sdio*) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  sdio_claim_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_release_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_sig (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

void brcmf_sdio_remove(struct brcmf_sdio *bus)
{
	brcmf_dbg(TRACE, "Enter\n");

	if (bus) {
		/* Stop watchdog task */
		if (bus->watchdog_tsk) {
			send_sig(SIGTERM, bus->watchdog_tsk, 1);
			kthread_stop(bus->watchdog_tsk);
			bus->watchdog_tsk = NULL;
		}

		/* De-register interrupt handler */
		brcmf_sdiod_intr_unregister(bus->sdiodev);

		brcmf_detach(bus->sdiodev->dev);

		cancel_work_sync(&bus->datawork);
		if (bus->brcmf_wq)
			destroy_workqueue(bus->brcmf_wq);

		if (bus->ci) {
			if (bus->sdiodev->state != BRCMF_SDIOD_NOMEDIUM) {
				sdio_claim_host(bus->sdiodev->func1);
				brcmf_sdio_wd_timer(bus, false);
				brcmf_sdio_clkctl(bus, CLK_AVAIL, false);
				/* Leave the device in state where it is
				 * 'passive'. This is done by resetting all
				 * necessary cores.
				 */
				msleep(20);
				brcmf_chip_set_passive(bus->ci);
				brcmf_sdio_clkctl(bus, CLK_NONE, false);
				sdio_release_host(bus->sdiodev->func1);
			}
			brcmf_chip_detach(bus->ci);
		}
		if (bus->sdiodev->settings)
			brcmf_release_module_param(bus->sdiodev->settings);

		kfree(bus->rxbuf);
		kfree(bus->hdrbuf);
		kfree(bus);
	}

	brcmf_dbg(TRACE, "Disconnected\n");
}