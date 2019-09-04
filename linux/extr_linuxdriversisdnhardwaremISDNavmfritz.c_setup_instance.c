#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_9__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
struct TYPE_11__ {int /*<<< orphan*/  ctrl; } ;
struct TYPE_16__ {int Bprotocols; int /*<<< orphan*/  bchannels; int /*<<< orphan*/  channelmap; TYPE_1__ D; } ;
struct TYPE_14__ {TYPE_7__ dev; } ;
struct TYPE_15__ {int /*<<< orphan*/  (* release ) (TYPE_5__*) ;TYPE_4__ dch; int /*<<< orphan*/ * hwlock; int /*<<< orphan*/  name; } ;
struct fritzcard {scalar_t__ type; int /*<<< orphan*/  list; TYPE_9__* bch; TYPE_5__ isac; int /*<<< orphan*/  addr; int /*<<< orphan*/  name; TYPE_3__* pdev; int /*<<< orphan*/  lock; } ;
struct TYPE_12__ {int nr; int /*<<< orphan*/  list; int /*<<< orphan*/  ctrl; int /*<<< orphan*/  send; } ;
struct TYPE_17__ {int nr; TYPE_2__ ch; struct fritzcard* hw; } ;
struct TYPE_13__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ AVM_FRITZ_PCIV2 ; 
 int AVM_cnt ; 
 int /*<<< orphan*/  Cards ; 
 unsigned short HDLC_FIFO_SIZE_V1 ; 
 unsigned short HDLC_FIFO_SIZE_V2 ; 
 int ISDN_P_B_HDLC ; 
 int ISDN_P_B_MASK ; 
 int ISDN_P_B_RAW ; 
 int /*<<< orphan*/  MAX_DATA_MEM ; 
 scalar_t__ MISDN_MAX_IDLEN ; 
 int /*<<< orphan*/  _set_debug (struct fritzcard*) ; 
 int /*<<< orphan*/  avm_bctrl ; 
 int /*<<< orphan*/  avm_dctrl ; 
 int /*<<< orphan*/  avm_l2l1B ; 
 int /*<<< orphan*/  card_lock ; 
 int init_card (struct fritzcard*) ; 
 int /*<<< orphan*/  kfree (struct fritzcard*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mISDN_freebchannel (TYPE_9__*) ; 
 int /*<<< orphan*/  mISDN_initbchannel (TYPE_9__*,int /*<<< orphan*/ ,unsigned short) ; 
 int mISDN_register_device (TYPE_7__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mISDN_unregister_device (TYPE_7__*) ; 
 int /*<<< orphan*/  mISDNisac_init (TYPE_5__*,struct fritzcard*) ; 
 int /*<<< orphan*/  pr_notice (char*,int) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_channelmap (int,int /*<<< orphan*/ ) ; 
 int setup_fritz (struct fritzcard*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,scalar_t__,char*,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*) ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
setup_instance(struct fritzcard *card)
{
	int i, err;
	unsigned short minsize;
	u_long flags;

	snprintf(card->name, MISDN_MAX_IDLEN - 1, "AVM.%d", AVM_cnt + 1);
	write_lock_irqsave(&card_lock, flags);
	list_add_tail(&card->list, &Cards);
	write_unlock_irqrestore(&card_lock, flags);

	_set_debug(card);
	card->isac.name = card->name;
	spin_lock_init(&card->lock);
	card->isac.hwlock = &card->lock;
	mISDNisac_init(&card->isac, card);

	card->isac.dch.dev.Bprotocols = (1 << (ISDN_P_B_RAW & ISDN_P_B_MASK)) |
		(1 << (ISDN_P_B_HDLC & ISDN_P_B_MASK));
	card->isac.dch.dev.D.ctrl = avm_dctrl;
	for (i = 0; i < 2; i++) {
		card->bch[i].nr = i + 1;
		set_channelmap(i + 1, card->isac.dch.dev.channelmap);
		if (AVM_FRITZ_PCIV2 == card->type)
			minsize = HDLC_FIFO_SIZE_V2;
		else
			minsize = HDLC_FIFO_SIZE_V1;
		mISDN_initbchannel(&card->bch[i], MAX_DATA_MEM, minsize);
		card->bch[i].hw = card;
		card->bch[i].ch.send = avm_l2l1B;
		card->bch[i].ch.ctrl = avm_bctrl;
		card->bch[i].ch.nr = i + 1;
		list_add(&card->bch[i].ch.list, &card->isac.dch.dev.bchannels);
	}
	err = setup_fritz(card);
	if (err)
		goto error;
	err = mISDN_register_device(&card->isac.dch.dev, &card->pdev->dev,
				    card->name);
	if (err)
		goto error_reg;
	err = init_card(card);
	if (!err)  {
		AVM_cnt++;
		pr_notice("AVM %d cards installed DEBUG\n", AVM_cnt);
		return 0;
	}
	mISDN_unregister_device(&card->isac.dch.dev);
error_reg:
	release_region(card->addr, 32);
error:
	card->isac.release(&card->isac);
	mISDN_freebchannel(&card->bch[1]);
	mISDN_freebchannel(&card->bch[0]);
	write_lock_irqsave(&card_lock, flags);
	list_del(&card->list);
	write_unlock_irqrestore(&card_lock, flags);
	kfree(card);
	return err;
}