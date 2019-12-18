#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct msb_data {int /*<<< orphan*/  q_lock; struct memstick_dev* card; } ;
struct memstick_dev {int /*<<< orphan*/  start; int /*<<< orphan*/  stop; int /*<<< orphan*/  check; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct msb_data*) ; 
 struct msb_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memstick_set_drvdata (struct memstick_dev*,struct msb_data*) ; 
 int /*<<< orphan*/  msb_check_card ; 
 int /*<<< orphan*/  msb_data_clear (struct msb_data*) ; 
 int msb_init_card (struct memstick_dev*) ; 
 int msb_init_disk (struct memstick_dev*) ; 
 int /*<<< orphan*/  msb_start ; 
 int /*<<< orphan*/  msb_stop ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int msb_probe(struct memstick_dev *card)
{
	struct msb_data *msb;
	int rc = 0;

	msb = kzalloc(sizeof(struct msb_data), GFP_KERNEL);
	if (!msb)
		return -ENOMEM;
	memstick_set_drvdata(card, msb);
	msb->card = card;
	spin_lock_init(&msb->q_lock);

	rc = msb_init_card(card);
	if (rc)
		goto out_free;

	rc = msb_init_disk(card);
	if (!rc) {
		card->check = msb_check_card;
		card->stop = msb_stop;
		card->start = msb_start;
		return 0;
	}
out_free:
	memstick_set_drvdata(card, NULL);
	msb_data_clear(msb);
	kfree(msb);
	return rc;
}