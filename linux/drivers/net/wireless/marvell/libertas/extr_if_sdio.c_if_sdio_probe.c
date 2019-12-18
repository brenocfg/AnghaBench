#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sdio_func {TYPE_2__* card; int /*<<< orphan*/  dev; int /*<<< orphan*/  device; int /*<<< orphan*/  vendor; int /*<<< orphan*/  class; } ;
struct sdio_device_id {int dummy; } ;
struct lbs_private {int is_polling; int /*<<< orphan*/  power_restore; int /*<<< orphan*/  power_save; int /*<<< orphan*/  reset_card; int /*<<< orphan*/  reset_deep_sleep_wakeup; int /*<<< orphan*/  exit_deep_sleep; int /*<<< orphan*/  enter_deep_sleep; int /*<<< orphan*/  hw_host_to_card; struct if_sdio_packet* card; } ;
struct if_sdio_packet {unsigned int model; struct if_sdio_packet* next; struct if_sdio_packet* packets; int /*<<< orphan*/  workqueue; struct lbs_private* priv; scalar_t__ ioport; int /*<<< orphan*/  pwron_waitq; int /*<<< orphan*/  packet_worker; int /*<<< orphan*/  lock; int /*<<< orphan*/  scratch_reg; struct sdio_func* func; } ;
struct if_sdio_card {unsigned int model; struct if_sdio_card* next; struct if_sdio_card* packets; int /*<<< orphan*/  workqueue; struct lbs_private* priv; scalar_t__ ioport; int /*<<< orphan*/  pwron_waitq; int /*<<< orphan*/  packet_worker; int /*<<< orphan*/  lock; int /*<<< orphan*/  scratch_reg; struct sdio_func* func; } ;
struct TYPE_7__ {int model; } ;
struct TYPE_6__ {int num_info; TYPE_1__* host; int /*<<< orphan*/ * info; } ;
struct TYPE_5__ {int caps; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_3__*) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IF_SDIO_FW_STATUS ; 
 int /*<<< orphan*/  IF_SDIO_SCRATCH ; 
 int /*<<< orphan*/  IF_SDIO_SCRATCH_OLD ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct lbs_private*) ; 
 int MMC_CAP_SDIO_IRQ ; 
#define  MODEL_8385 130 
#define  MODEL_8686 129 
#define  MODEL_8688 128 
 int PTR_ERR (struct lbs_private*) ; 
 int /*<<< orphan*/  WQ_MEM_RECLAIM ; 
 int /*<<< orphan*/  alloc_workqueue (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 TYPE_3__* fw_table ; 
 int /*<<< orphan*/  if_sdio_enter_deep_sleep ; 
 int /*<<< orphan*/  if_sdio_exit_deep_sleep ; 
 int /*<<< orphan*/  if_sdio_host_to_card ; 
 int /*<<< orphan*/  if_sdio_host_to_card_worker ; 
 int if_sdio_power_on (struct if_sdio_packet*) ; 
 int /*<<< orphan*/  if_sdio_power_restore ; 
 int /*<<< orphan*/  if_sdio_power_save ; 
 int /*<<< orphan*/  if_sdio_reset_card ; 
 int /*<<< orphan*/  if_sdio_reset_deep_sleep_wakeup ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct if_sdio_packet*) ; 
 struct if_sdio_packet* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct lbs_private* lbs_add_card (struct if_sdio_packet*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lbs_deb_sdio (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  lbs_remove_card (struct lbs_private*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  sdio_set_drvdata (struct sdio_func*,struct if_sdio_packet*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int sscanf (int /*<<< orphan*/ ,char*,unsigned int*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int if_sdio_probe(struct sdio_func *func,
		const struct sdio_device_id *id)
{
	struct if_sdio_card *card;
	struct lbs_private *priv;
	int ret, i;
	unsigned int model;
	struct if_sdio_packet *packet;

	for (i = 0;i < func->card->num_info;i++) {
		if (sscanf(func->card->info[i],
				"802.11 SDIO ID: %x", &model) == 1)
			break;
		if (sscanf(func->card->info[i],
				"ID: %x", &model) == 1)
			break;
		if (!strcmp(func->card->info[i], "IBIS Wireless SDIO Card")) {
			model = MODEL_8385;
			break;
		}
	}

	if (i == func->card->num_info) {
		pr_err("unable to identify card model\n");
		return -ENODEV;
	}

	card = kzalloc(sizeof(struct if_sdio_card), GFP_KERNEL);
	if (!card)
		return -ENOMEM;

	card->func = func;
	card->model = model;

	switch (card->model) {
	case MODEL_8385:
		card->scratch_reg = IF_SDIO_SCRATCH_OLD;
		break;
	case MODEL_8686:
		card->scratch_reg = IF_SDIO_SCRATCH;
		break;
	case MODEL_8688:
	default: /* for newer chipsets */
		card->scratch_reg = IF_SDIO_FW_STATUS;
		break;
	}

	spin_lock_init(&card->lock);
	card->workqueue = alloc_workqueue("libertas_sdio", WQ_MEM_RECLAIM, 0);
	INIT_WORK(&card->packet_worker, if_sdio_host_to_card_worker);
	init_waitqueue_head(&card->pwron_waitq);

	/* Check if we support this card */
	for (i = 0; i < ARRAY_SIZE(fw_table); i++) {
		if (card->model == fw_table[i].model)
			break;
	}
	if (i == ARRAY_SIZE(fw_table)) {
		pr_err("unknown card model 0x%x\n", card->model);
		ret = -ENODEV;
		goto free;
	}

	sdio_set_drvdata(func, card);

	lbs_deb_sdio("class = 0x%X, vendor = 0x%X, "
			"device = 0x%X, model = 0x%X, ioport = 0x%X\n",
			func->class, func->vendor, func->device,
			model, (unsigned)card->ioport);


	priv = lbs_add_card(card, &func->dev);
	if (IS_ERR(priv)) {
		ret = PTR_ERR(priv);
		goto free;
	}

	card->priv = priv;

	priv->card = card;
	priv->hw_host_to_card = if_sdio_host_to_card;
	priv->enter_deep_sleep = if_sdio_enter_deep_sleep;
	priv->exit_deep_sleep = if_sdio_exit_deep_sleep;
	priv->reset_deep_sleep_wakeup = if_sdio_reset_deep_sleep_wakeup;
	priv->reset_card = if_sdio_reset_card;
	priv->power_save = if_sdio_power_save;
	priv->power_restore = if_sdio_power_restore;
	priv->is_polling = !(func->card->host->caps & MMC_CAP_SDIO_IRQ);
	ret = if_sdio_power_on(card);
	if (ret)
		goto err_activate_card;

out:
	return ret;

err_activate_card:
	flush_workqueue(card->workqueue);
	lbs_remove_card(priv);
free:
	destroy_workqueue(card->workqueue);
	while (card->packets) {
		packet = card->packets;
		card->packets = card->packets->next;
		kfree(packet);
	}

	kfree(card);

	goto out;
}