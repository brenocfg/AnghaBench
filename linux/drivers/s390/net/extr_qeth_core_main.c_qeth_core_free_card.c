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
struct qeth_card {TYPE_1__* gdev; int /*<<< orphan*/  qeth_service_level; int /*<<< orphan*/  event_wq; int /*<<< orphan*/  read_cmd; int /*<<< orphan*/  data; int /*<<< orphan*/  write; int /*<<< orphan*/  read; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct qeth_card*) ; 
 int /*<<< orphan*/  qeth_clean_channel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qeth_free_qdio_queues (struct qeth_card*) ; 
 int /*<<< orphan*/  qeth_put_cmd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_service_level (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qeth_core_free_card(struct qeth_card *card)
{
	QETH_CARD_TEXT(card, 2, "freecrd");
	qeth_clean_channel(&card->read);
	qeth_clean_channel(&card->write);
	qeth_clean_channel(&card->data);
	qeth_put_cmd(card->read_cmd);
	destroy_workqueue(card->event_wq);
	qeth_free_qdio_queues(card);
	unregister_service_level(&card->qeth_service_level);
	dev_set_drvdata(&card->gdev->dev, NULL);
	kfree(card);
}