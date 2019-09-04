#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_9__ ;
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_15__ ;
typedef  struct TYPE_22__   TYPE_13__ ;
typedef  struct TYPE_21__   TYPE_12__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tag ;
struct TYPE_27__ {void* virt; void* pool; int /*<<< orphan*/  phys; } ;
struct TYPE_28__ {void* virt; void* pool; int /*<<< orphan*/  phys; } ;
struct TYPE_29__ {unsigned int count; void* busy; void* allocated; int /*<<< orphan*/  lock; } ;
struct TYPE_23__ {int tx_block; int knows_txdone; int /*<<< orphan*/  rx_callback; TYPE_12__* dev; } ;
struct TYPE_26__ {int /*<<< orphan*/  channel; TYPE_15__ client; } ;
struct tegra_bpmp {TYPE_4__ tx; TYPE_5__ rx; TYPE_9__* tx_channel; TYPE_9__* rx_channel; TYPE_9__* threaded_channels; TYPE_6__ threaded; TYPE_3__ mbox; TYPE_13__* soc; int /*<<< orphan*/  atomic_tx_lock; int /*<<< orphan*/  lock; int /*<<< orphan*/  mrqs; TYPE_12__* dev; } ;
struct TYPE_21__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_12__ dev; } ;
struct TYPE_32__ {scalar_t__ bpmp; } ;
struct TYPE_30__ {unsigned int count; scalar_t__ offset; } ;
struct TYPE_25__ {scalar_t__ offset; } ;
struct TYPE_24__ {scalar_t__ offset; } ;
struct TYPE_31__ {TYPE_7__ thread; TYPE_2__ cpu_rx; TYPE_1__ cpu_tx; } ;
struct TYPE_22__ {TYPE_8__ channels; } ;

/* Variables and functions */
 int BITS_TO_LONGS (unsigned int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MRQ_PING ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_12__*,char*,...) ; 
 int /*<<< orphan*/  dev_info (TYPE_12__*,char*,char*) ; 
 TYPE_9__* devm_kcalloc (TYPE_12__*,unsigned int,int,int /*<<< orphan*/ ) ; 
 void* devm_kzalloc (TYPE_12__*,int,int /*<<< orphan*/ ) ; 
 void* gen_pool_dma_alloc (void*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gen_pool_free (void*,unsigned long,int) ; 
 int /*<<< orphan*/  mbox_free_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbox_request_channel (TYPE_15__*,int /*<<< orphan*/ ) ; 
 TYPE_13__* of_device_get_match_data (TYPE_12__*) ; 
 void* of_gen_pool_get (int /*<<< orphan*/ ,char*,int) ; 
 int of_platform_default_populate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_12__*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct tegra_bpmp*) ; 
 int /*<<< orphan*/  sema_init (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tegra_bpmp_channel_cleanup (TYPE_9__*) ; 
 int tegra_bpmp_channel_init (TYPE_9__*,struct tegra_bpmp*,scalar_t__) ; 
 int /*<<< orphan*/  tegra_bpmp_channel_reset (TYPE_9__*) ; 
 int /*<<< orphan*/  tegra_bpmp_free_mrq (struct tegra_bpmp*,int /*<<< orphan*/ ,struct tegra_bpmp*) ; 
 int tegra_bpmp_get_firmware_tag (struct tegra_bpmp*,char*,int) ; 
 int /*<<< orphan*/  tegra_bpmp_handle_rx ; 
 int tegra_bpmp_init_clocks (struct tegra_bpmp*) ; 
 int tegra_bpmp_init_debugfs (struct tegra_bpmp*) ; 
 int tegra_bpmp_init_powergates (struct tegra_bpmp*) ; 
 int tegra_bpmp_init_resets (struct tegra_bpmp*) ; 
 int /*<<< orphan*/  tegra_bpmp_mrq_handle_ping ; 
 int tegra_bpmp_ping (struct tegra_bpmp*) ; 
 int tegra_bpmp_request_mrq (struct tegra_bpmp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tegra_bpmp*) ; 

__attribute__((used)) static int tegra_bpmp_probe(struct platform_device *pdev)
{
	struct tegra_bpmp *bpmp;
	unsigned int i;
	char tag[32];
	size_t size;
	int err;

	bpmp = devm_kzalloc(&pdev->dev, sizeof(*bpmp), GFP_KERNEL);
	if (!bpmp)
		return -ENOMEM;

	bpmp->soc = of_device_get_match_data(&pdev->dev);
	bpmp->dev = &pdev->dev;

	bpmp->tx.pool = of_gen_pool_get(pdev->dev.of_node, "shmem", 0);
	if (!bpmp->tx.pool) {
		dev_err(&pdev->dev, "TX shmem pool not found\n");
		return -ENOMEM;
	}

	bpmp->tx.virt = gen_pool_dma_alloc(bpmp->tx.pool, 4096, &bpmp->tx.phys);
	if (!bpmp->tx.virt) {
		dev_err(&pdev->dev, "failed to allocate from TX pool\n");
		return -ENOMEM;
	}

	bpmp->rx.pool = of_gen_pool_get(pdev->dev.of_node, "shmem", 1);
	if (!bpmp->rx.pool) {
		dev_err(&pdev->dev, "RX shmem pool not found\n");
		err = -ENOMEM;
		goto free_tx;
	}

	bpmp->rx.virt = gen_pool_dma_alloc(bpmp->rx.pool, 4096, &bpmp->rx.phys);
	if (!bpmp->rx.virt) {
		dev_err(&pdev->dev, "failed to allocate from RX pool\n");
		err = -ENOMEM;
		goto free_tx;
	}

	INIT_LIST_HEAD(&bpmp->mrqs);
	spin_lock_init(&bpmp->lock);

	bpmp->threaded.count = bpmp->soc->channels.thread.count;
	sema_init(&bpmp->threaded.lock, bpmp->threaded.count);

	size = BITS_TO_LONGS(bpmp->threaded.count) * sizeof(long);

	bpmp->threaded.allocated = devm_kzalloc(&pdev->dev, size, GFP_KERNEL);
	if (!bpmp->threaded.allocated) {
		err = -ENOMEM;
		goto free_rx;
	}

	bpmp->threaded.busy = devm_kzalloc(&pdev->dev, size, GFP_KERNEL);
	if (!bpmp->threaded.busy) {
		err = -ENOMEM;
		goto free_rx;
	}

	spin_lock_init(&bpmp->atomic_tx_lock);
	bpmp->tx_channel = devm_kzalloc(&pdev->dev, sizeof(*bpmp->tx_channel),
					GFP_KERNEL);
	if (!bpmp->tx_channel) {
		err = -ENOMEM;
		goto free_rx;
	}

	bpmp->rx_channel = devm_kzalloc(&pdev->dev, sizeof(*bpmp->rx_channel),
	                                GFP_KERNEL);
	if (!bpmp->rx_channel) {
		err = -ENOMEM;
		goto free_rx;
	}

	bpmp->threaded_channels = devm_kcalloc(&pdev->dev, bpmp->threaded.count,
					       sizeof(*bpmp->threaded_channels),
					       GFP_KERNEL);
	if (!bpmp->threaded_channels) {
		err = -ENOMEM;
		goto free_rx;
	}

	err = tegra_bpmp_channel_init(bpmp->tx_channel, bpmp,
				      bpmp->soc->channels.cpu_tx.offset);
	if (err < 0)
		goto free_rx;

	err = tegra_bpmp_channel_init(bpmp->rx_channel, bpmp,
				      bpmp->soc->channels.cpu_rx.offset);
	if (err < 0)
		goto cleanup_tx_channel;

	for (i = 0; i < bpmp->threaded.count; i++) {
		err = tegra_bpmp_channel_init(
			&bpmp->threaded_channels[i], bpmp,
			bpmp->soc->channels.thread.offset + i);
		if (err < 0)
			goto cleanup_threaded_channels;
	}

	/* mbox registration */
	bpmp->mbox.client.dev = &pdev->dev;
	bpmp->mbox.client.rx_callback = tegra_bpmp_handle_rx;
	bpmp->mbox.client.tx_block = false;
	bpmp->mbox.client.knows_txdone = false;

	bpmp->mbox.channel = mbox_request_channel(&bpmp->mbox.client, 0);
	if (IS_ERR(bpmp->mbox.channel)) {
		err = PTR_ERR(bpmp->mbox.channel);
		dev_err(&pdev->dev, "failed to get HSP mailbox: %d\n", err);
		goto cleanup_threaded_channels;
	}

	/* reset message channels */
	tegra_bpmp_channel_reset(bpmp->tx_channel);
	tegra_bpmp_channel_reset(bpmp->rx_channel);
	for (i = 0; i < bpmp->threaded.count; i++)
		tegra_bpmp_channel_reset(&bpmp->threaded_channels[i]);

	err = tegra_bpmp_request_mrq(bpmp, MRQ_PING,
				     tegra_bpmp_mrq_handle_ping, bpmp);
	if (err < 0)
		goto free_mbox;

	err = tegra_bpmp_ping(bpmp);
	if (err < 0) {
		dev_err(&pdev->dev, "failed to ping BPMP: %d\n", err);
		goto free_mrq;
	}

	err = tegra_bpmp_get_firmware_tag(bpmp, tag, sizeof(tag) - 1);
	if (err < 0) {
		dev_err(&pdev->dev, "failed to get firmware tag: %d\n", err);
		goto free_mrq;
	}

	dev_info(&pdev->dev, "firmware: %s\n", tag);

	platform_set_drvdata(pdev, bpmp);

	err = of_platform_default_populate(pdev->dev.of_node, NULL, &pdev->dev);
	if (err < 0)
		goto free_mrq;

	err = tegra_bpmp_init_clocks(bpmp);
	if (err < 0)
		goto free_mrq;

	err = tegra_bpmp_init_resets(bpmp);
	if (err < 0)
		goto free_mrq;

	err = tegra_bpmp_init_powergates(bpmp);
	if (err < 0)
		goto free_mrq;

	err = tegra_bpmp_init_debugfs(bpmp);
	if (err < 0)
		dev_err(&pdev->dev, "debugfs initialization failed: %d\n", err);

	return 0;

free_mrq:
	tegra_bpmp_free_mrq(bpmp, MRQ_PING, bpmp);
free_mbox:
	mbox_free_channel(bpmp->mbox.channel);
cleanup_threaded_channels:
	for (i = 0; i < bpmp->threaded.count; i++) {
		if (bpmp->threaded_channels[i].bpmp)
			tegra_bpmp_channel_cleanup(&bpmp->threaded_channels[i]);
	}

	tegra_bpmp_channel_cleanup(bpmp->rx_channel);
cleanup_tx_channel:
	tegra_bpmp_channel_cleanup(bpmp->tx_channel);
free_rx:
	gen_pool_free(bpmp->rx.pool, (unsigned long)bpmp->rx.virt, 4096);
free_tx:
	gen_pool_free(bpmp->tx.pool, (unsigned long)bpmp->tx.virt, 4096);
	return err;
}