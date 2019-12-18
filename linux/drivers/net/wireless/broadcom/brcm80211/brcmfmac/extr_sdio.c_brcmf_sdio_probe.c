#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct workqueue_struct {int dummy; } ;
struct brcmf_sdio_dev {int /*<<< orphan*/  dev; TYPE_1__* func1; TYPE_2__* func2; struct brcmf_sdio* bus; } ;
struct brcmf_sdio {int dpc_triggered; int dpc_running; int rxflow; int sr_enabled; int /*<<< orphan*/  idleclock; int /*<<< orphan*/  idletime; int /*<<< orphan*/  clkstate; struct brcmf_sdio_dev* sdiodev; int /*<<< orphan*/  blocksize; int /*<<< orphan*/  roundup; scalar_t__ tx_hdrlen; int /*<<< orphan*/ * watchdog_tsk; int /*<<< orphan*/  watchdog_wait; int /*<<< orphan*/  timer; int /*<<< orphan*/  dcmd_resp_wait; int /*<<< orphan*/  ctrl_wait; int /*<<< orphan*/  txq_lock; int /*<<< orphan*/  rxctl_lock; struct workqueue_struct* brcmf_wq; int /*<<< orphan*/  datawork; scalar_t__ tx_seq; int /*<<< orphan*/  txminmax; int /*<<< orphan*/  rxbound; int /*<<< orphan*/  txbound; int /*<<< orphan*/  glom; } ;
struct brcmf_fw_request {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  cur_blksize; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMF_IDLE_ACTIVE ; 
 int /*<<< orphan*/  BRCMF_IDLE_INTERVAL ; 
 int /*<<< orphan*/  BRCMF_RXBOUND ; 
 int /*<<< orphan*/  BRCMF_TXBOUND ; 
 int /*<<< orphan*/  BRCMF_TXMINMAX ; 
 int /*<<< orphan*/  CLK_SDONLY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INFO ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SBSDIO_FUNC1_CHIPCLKCSR ; 
 scalar_t__ SDPCM_HWHDR_LEN ; 
 scalar_t__ SDPCM_SEQ_WRAP ; 
 scalar_t__ SDPCM_SWHDR_LEN ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  WQ_MEM_RECLAIM ; 
 struct workqueue_struct* alloc_ordered_workqueue (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  brcmf_err (char*,...) ; 
 int brcmf_fw_get_firmwares (int /*<<< orphan*/ ,struct brcmf_fw_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_sdio_dataworker ; 
 int /*<<< orphan*/  brcmf_sdio_firmware_callback ; 
 struct brcmf_fw_request* brcmf_sdio_prepare_fw_request (struct brcmf_sdio*) ; 
 int /*<<< orphan*/  brcmf_sdio_probe_attach (struct brcmf_sdio*) ; 
 int /*<<< orphan*/  brcmf_sdio_remove (struct brcmf_sdio*) ; 
 int /*<<< orphan*/  brcmf_sdio_watchdog ; 
 int /*<<< orphan*/  brcmf_sdio_watchdog_thread ; 
 int /*<<< orphan*/  brcmf_sdiod_freezer_count (struct brcmf_sdio_dev*) ; 
 int /*<<< orphan*/  brcmf_sdiod_writeb (struct brcmf_sdio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct brcmf_fw_request*) ; 
 int /*<<< orphan*/ * kthread_run (int /*<<< orphan*/ ,struct brcmf_sdio*,char*,int /*<<< orphan*/ ) ; 
 struct brcmf_sdio* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max_roundup ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  sdio_claim_host (TYPE_1__*) ; 
 int /*<<< orphan*/  sdio_disable_func (TYPE_2__*) ; 
 int /*<<< orphan*/  sdio_release_host (TYPE_1__*) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct brcmf_sdio *brcmf_sdio_probe(struct brcmf_sdio_dev *sdiodev)
{
	int ret;
	struct brcmf_sdio *bus;
	struct workqueue_struct *wq;
	struct brcmf_fw_request *fwreq;

	brcmf_dbg(TRACE, "Enter\n");

	/* Allocate private bus interface state */
	bus = kzalloc(sizeof(struct brcmf_sdio), GFP_ATOMIC);
	if (!bus)
		goto fail;

	bus->sdiodev = sdiodev;
	sdiodev->bus = bus;
	skb_queue_head_init(&bus->glom);
	bus->txbound = BRCMF_TXBOUND;
	bus->rxbound = BRCMF_RXBOUND;
	bus->txminmax = BRCMF_TXMINMAX;
	bus->tx_seq = SDPCM_SEQ_WRAP - 1;

	/* single-threaded workqueue */
	wq = alloc_ordered_workqueue("brcmf_wq/%s", WQ_MEM_RECLAIM,
				     dev_name(&sdiodev->func1->dev));
	if (!wq) {
		brcmf_err("insufficient memory to create txworkqueue\n");
		goto fail;
	}
	brcmf_sdiod_freezer_count(sdiodev);
	INIT_WORK(&bus->datawork, brcmf_sdio_dataworker);
	bus->brcmf_wq = wq;

	/* attempt to attach to the dongle */
	if (!(brcmf_sdio_probe_attach(bus))) {
		brcmf_err("brcmf_sdio_probe_attach failed\n");
		goto fail;
	}

	spin_lock_init(&bus->rxctl_lock);
	spin_lock_init(&bus->txq_lock);
	init_waitqueue_head(&bus->ctrl_wait);
	init_waitqueue_head(&bus->dcmd_resp_wait);

	/* Set up the watchdog timer */
	timer_setup(&bus->timer, brcmf_sdio_watchdog, 0);
	/* Initialize watchdog thread */
	init_completion(&bus->watchdog_wait);
	bus->watchdog_tsk = kthread_run(brcmf_sdio_watchdog_thread,
					bus, "brcmf_wdog/%s",
					dev_name(&sdiodev->func1->dev));
	if (IS_ERR(bus->watchdog_tsk)) {
		pr_warn("brcmf_watchdog thread failed to start\n");
		bus->watchdog_tsk = NULL;
	}
	/* Initialize DPC thread */
	bus->dpc_triggered = false;
	bus->dpc_running = false;

	/* default sdio bus header length for tx packet */
	bus->tx_hdrlen = SDPCM_HWHDR_LEN + SDPCM_SWHDR_LEN;

	/* Query the F2 block size, set roundup accordingly */
	bus->blocksize = bus->sdiodev->func2->cur_blksize;
	bus->roundup = min(max_roundup, bus->blocksize);

	sdio_claim_host(bus->sdiodev->func1);

	/* Disable F2 to clear any intermediate frame state on the dongle */
	sdio_disable_func(bus->sdiodev->func2);

	bus->rxflow = false;

	/* Done with backplane-dependent accesses, can drop clock... */
	brcmf_sdiod_writeb(bus->sdiodev, SBSDIO_FUNC1_CHIPCLKCSR, 0, NULL);

	sdio_release_host(bus->sdiodev->func1);

	/* ...and initialize clock/power states */
	bus->clkstate = CLK_SDONLY;
	bus->idletime = BRCMF_IDLE_INTERVAL;
	bus->idleclock = BRCMF_IDLE_ACTIVE;

	/* SR state */
	bus->sr_enabled = false;

	brcmf_dbg(INFO, "completed!!\n");

	fwreq = brcmf_sdio_prepare_fw_request(bus);
	if (!fwreq) {
		ret = -ENOMEM;
		goto fail;
	}

	ret = brcmf_fw_get_firmwares(sdiodev->dev, fwreq,
				     brcmf_sdio_firmware_callback);
	if (ret != 0) {
		brcmf_err("async firmware request failed: %d\n", ret);
		kfree(fwreq);
		goto fail;
	}

	return bus;

fail:
	brcmf_sdio_remove(bus);
	return NULL;
}