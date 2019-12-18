#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ulong ;
struct TYPE_14__ {scalar_t__ Bprotocols; } ;
struct TYPE_11__ {TYPE_7__ dev; } ;
struct TYPE_12__ {TYPE_3__ dch; int /*<<< orphan*/ * hwlock; int /*<<< orphan*/  name; } ;
struct TYPE_13__ {int /*<<< orphan*/  (* release ) (TYPE_5__*) ;TYPE_4__ isac; void* ctrl; int /*<<< orphan*/ * hwlock; int /*<<< orphan*/  owner; int /*<<< orphan*/  name; } ;
struct inf_hw {int /*<<< orphan*/  list; TYPE_5__ ipac; int /*<<< orphan*/  name; TYPE_2__* pdev; int /*<<< orphan*/  lock; TYPE_1__* ci; } ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;
struct TYPE_9__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  Cards ; 
 scalar_t__ MISDN_MAX_IDLEN ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  _set_debug (struct inf_hw*) ; 
 int /*<<< orphan*/  card_lock ; 
 int inf_cnt ; 
 int /*<<< orphan*/  inf_ctrl ; 
 int init_irq (struct inf_hw*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int mISDN_register_device (TYPE_7__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mISDN_unregister_device (TYPE_7__*) ; 
 scalar_t__ mISDNipac_init (TYPE_5__*,struct inf_hw*) ; 
 int /*<<< orphan*/  pr_notice (char*,int) ; 
 int /*<<< orphan*/  release_io (struct inf_hw*) ; 
 int setup_io (struct inf_hw*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,scalar_t__,char*,char*,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*) ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
setup_instance(struct inf_hw *card)
{
	int err;
	ulong flags;

	snprintf(card->name, MISDN_MAX_IDLEN - 1, "%s.%d", card->ci->name,
		 inf_cnt + 1);
	write_lock_irqsave(&card_lock, flags);
	list_add_tail(&card->list, &Cards);
	write_unlock_irqrestore(&card_lock, flags);

	_set_debug(card);
	card->ipac.isac.name = card->name;
	card->ipac.name = card->name;
	card->ipac.owner = THIS_MODULE;
	spin_lock_init(&card->lock);
	card->ipac.isac.hwlock = &card->lock;
	card->ipac.hwlock = &card->lock;
	card->ipac.ctrl = (void *)&inf_ctrl;

	err = setup_io(card);
	if (err)
		goto error_setup;

	card->ipac.isac.dch.dev.Bprotocols =
		mISDNipac_init(&card->ipac, card);

	if (card->ipac.isac.dch.dev.Bprotocols == 0)
		goto error_setup;

	err = mISDN_register_device(&card->ipac.isac.dch.dev,
				    &card->pdev->dev, card->name);
	if (err)
		goto error;

	err = init_irq(card);
	if (!err)  {
		inf_cnt++;
		pr_notice("Infineon %d cards installed\n", inf_cnt);
		return 0;
	}
	mISDN_unregister_device(&card->ipac.isac.dch.dev);
error:
	card->ipac.release(&card->ipac);
error_setup:
	release_io(card);
	write_lock_irqsave(&card_lock, flags);
	list_del(&card->list);
	write_unlock_irqrestore(&card_lock, flags);
	return err;
}