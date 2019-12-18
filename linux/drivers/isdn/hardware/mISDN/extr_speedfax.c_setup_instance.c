#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_13__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
struct TYPE_22__ {int (* init ) (TYPE_6__*) ;int (* firmware ) (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* release ) (TYPE_6__*) ;TYPE_4__* ch; int /*<<< orphan*/  owner; int /*<<< orphan*/  name; void* ctrl; int /*<<< orphan*/ * hwlock; } ;
struct TYPE_17__ {int /*<<< orphan*/  ctrl; } ;
struct TYPE_16__ {int /*<<< orphan*/  bchannels; int /*<<< orphan*/  channelmap; int /*<<< orphan*/  Bprotocols; TYPE_1__ D; } ;
struct TYPE_21__ {TYPE_13__ dev; } ;
struct TYPE_23__ {int /*<<< orphan*/  (* release ) (TYPE_7__*) ;TYPE_5__ dch; int /*<<< orphan*/  name; int /*<<< orphan*/ * hwlock; } ;
struct sfax_hw {int /*<<< orphan*/  list; TYPE_10__* pdev; TYPE_6__ isar; TYPE_7__ isac; int /*<<< orphan*/  cfg; int /*<<< orphan*/  irq; int /*<<< orphan*/  name; int /*<<< orphan*/  lock; } ;
struct firmware {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct TYPE_18__ {int /*<<< orphan*/  list; } ;
struct TYPE_19__ {TYPE_2__ ch; } ;
struct TYPE_20__ {TYPE_3__ bch; } ;
struct TYPE_15__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  Cards ; 
 int DEBUG_HW ; 
 scalar_t__ MISDN_MAX_IDLEN ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  _set_debug (struct sfax_hw*) ; 
 int /*<<< orphan*/  card_lock ; 
 int debug ; 
 int /*<<< orphan*/  disable_hwirq (struct sfax_hw*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct sfax_hw*) ; 
 int init_card (struct sfax_hw*) ; 
 int /*<<< orphan*/  kfree (struct sfax_hw*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int mISDN_register_device (TYPE_13__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mISDN_unregister_device (TYPE_13__*) ; 
 int /*<<< orphan*/  mISDNisac_init (TYPE_7__*,struct sfax_hw*) ; 
 int /*<<< orphan*/  mISDNisar_init (TYPE_6__*,struct sfax_hw*) ; 
 int /*<<< orphan*/  pci_disable_device (TYPE_10__*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_notice (char*,int,...) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int) ; 
 int request_firmware (struct firmware const**,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_channelmap (int,int /*<<< orphan*/ ) ; 
 int setup_speedfax (struct sfax_hw*) ; 
 int sfax_cnt ; 
 int /*<<< orphan*/  sfax_ctrl ; 
 int /*<<< orphan*/  sfax_dctrl ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,scalar_t__,char*,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_6__*) ; 
 int stub2 (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (TYPE_7__*) ; 
 int /*<<< orphan*/  stub4 (TYPE_6__*) ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
setup_instance(struct sfax_hw *card)
{
	const struct firmware *firmware;
	int i, err;
	u_long flags;

	snprintf(card->name, MISDN_MAX_IDLEN - 1, "Speedfax.%d", sfax_cnt + 1);
	write_lock_irqsave(&card_lock, flags);
	list_add_tail(&card->list, &Cards);
	write_unlock_irqrestore(&card_lock, flags);
	_set_debug(card);
	spin_lock_init(&card->lock);
	card->isac.hwlock = &card->lock;
	card->isar.hwlock = &card->lock;
	card->isar.ctrl = (void *)&sfax_ctrl;
	card->isac.name = card->name;
	card->isar.name = card->name;
	card->isar.owner = THIS_MODULE;

	err = request_firmware(&firmware, "isdn/ISAR.BIN", &card->pdev->dev);
	if (err < 0) {
		pr_info("%s: firmware request failed %d\n",
			card->name, err);
		goto error_fw;
	}
	if (debug & DEBUG_HW)
		pr_notice("%s: got firmware %zu bytes\n",
			  card->name, firmware->size);

	mISDNisac_init(&card->isac, card);

	card->isac.dch.dev.D.ctrl = sfax_dctrl;
	card->isac.dch.dev.Bprotocols =
		mISDNisar_init(&card->isar, card);
	for (i = 0; i < 2; i++) {
		set_channelmap(i + 1, card->isac.dch.dev.channelmap);
		list_add(&card->isar.ch[i].bch.ch.list,
			 &card->isac.dch.dev.bchannels);
	}

	err = setup_speedfax(card);
	if (err)
		goto error_setup;
	err = card->isar.init(&card->isar);
	if (err)
		goto error;
	err = mISDN_register_device(&card->isac.dch.dev,
				    &card->pdev->dev, card->name);
	if (err)
		goto error;
	err = init_card(card);
	if (err)
		goto error_init;
	err = card->isar.firmware(&card->isar, firmware->data, firmware->size);
	if (!err)  {
		release_firmware(firmware);
		sfax_cnt++;
		pr_notice("SpeedFax %d cards installed\n", sfax_cnt);
		return 0;
	}
	disable_hwirq(card);
	free_irq(card->irq, card);
error_init:
	mISDN_unregister_device(&card->isac.dch.dev);
error:
	release_region(card->cfg, 256);
error_setup:
	card->isac.release(&card->isac);
	card->isar.release(&card->isar);
	release_firmware(firmware);
error_fw:
	pci_disable_device(card->pdev);
	write_lock_irqsave(&card_lock, flags);
	list_del(&card->list);
	write_unlock_irqrestore(&card_lock, flags);
	kfree(card);
	return err;
}