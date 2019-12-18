#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* card; int /*<<< orphan*/  ncci_head; } ;
typedef  TYPE_1__ avmctrl_info ;
struct TYPE_8__ {int nr_controllers; int /*<<< orphan*/  lock; TYPE_1__* ctrlinfo; } ;
typedef  TYPE_2__ avmcard ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 TYPE_1__* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 TYPE_2__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

avmcard *b1_alloc_card(int nr_controllers)
{
	avmcard *card;
	avmctrl_info *cinfo;
	int i;

	card = kzalloc(sizeof(*card), GFP_KERNEL);
	if (!card)
		return NULL;

	cinfo = kcalloc(nr_controllers, sizeof(*cinfo), GFP_KERNEL);
	if (!cinfo) {
		kfree(card);
		return NULL;
	}

	card->ctrlinfo = cinfo;
	for (i = 0; i < nr_controllers; i++) {
		INIT_LIST_HEAD(&cinfo[i].ncci_head);
		cinfo[i].card = card;
	}
	spin_lock_init(&card->lock);
	card->nr_controllers = nr_controllers;

	return card;
}