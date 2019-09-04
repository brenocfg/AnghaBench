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
struct mspro_block_data {int /*<<< orphan*/  attr_group; int /*<<< orphan*/  q_lock; struct memstick_dev* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct memstick_dev {TYPE_1__ dev; int /*<<< orphan*/  start; int /*<<< orphan*/  stop; int /*<<< orphan*/  check; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct mspro_block_data*) ; 
 struct mspro_block_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memstick_set_drvdata (struct memstick_dev*,struct mspro_block_data*) ; 
 int /*<<< orphan*/  mspro_block_check_card ; 
 int /*<<< orphan*/  mspro_block_data_clear (struct mspro_block_data*) ; 
 int mspro_block_init_card (struct memstick_dev*) ; 
 int mspro_block_init_disk (struct memstick_dev*) ; 
 int /*<<< orphan*/  mspro_block_start ; 
 int /*<<< orphan*/  mspro_block_stop ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mspro_block_probe(struct memstick_dev *card)
{
	struct mspro_block_data *msb;
	int rc = 0;

	msb = kzalloc(sizeof(struct mspro_block_data), GFP_KERNEL);
	if (!msb)
		return -ENOMEM;
	memstick_set_drvdata(card, msb);
	msb->card = card;
	spin_lock_init(&msb->q_lock);

	rc = mspro_block_init_card(card);

	if (rc)
		goto out_free;

	rc = sysfs_create_group(&card->dev.kobj, &msb->attr_group);
	if (rc)
		goto out_free;

	rc = mspro_block_init_disk(card);
	if (!rc) {
		card->check = mspro_block_check_card;
		card->stop = mspro_block_stop;
		card->start = mspro_block_start;
		return 0;
	}

	sysfs_remove_group(&card->dev.kobj, &msb->attr_group);
out_free:
	memstick_set_drvdata(card, NULL);
	mspro_block_data_clear(msb);
	kfree(msb);
	return rc;
}