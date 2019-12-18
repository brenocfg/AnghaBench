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
struct qeth_card {int /*<<< orphan*/  dev; TYPE_1__* discipline; } ;
struct ccwgroup_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* remove ) (struct ccwgroup_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 struct qeth_card* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_netdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qeth_core_free_card (struct qeth_card*) ; 
 int /*<<< orphan*/  qeth_core_free_discipline (struct qeth_card*) ; 
 int /*<<< orphan*/  stub1 (struct ccwgroup_device*) ; 

__attribute__((used)) static void qeth_core_remove_device(struct ccwgroup_device *gdev)
{
	struct qeth_card *card = dev_get_drvdata(&gdev->dev);

	QETH_CARD_TEXT(card, 2, "removedv");

	if (card->discipline) {
		card->discipline->remove(gdev);
		qeth_core_free_discipline(card);
	}

	free_netdev(card->dev);
	qeth_core_free_card(card);
	put_device(&gdev->dev);
}