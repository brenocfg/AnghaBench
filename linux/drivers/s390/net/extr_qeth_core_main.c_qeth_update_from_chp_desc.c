#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ func_level; } ;
struct TYPE_4__ {scalar_t__ no_out_queues; } ;
struct TYPE_6__ {struct ccw_device* ccwdev; } ;
struct qeth_card {TYPE_2__ info; TYPE_1__ qdio; TYPE_3__ data; } ;
struct channel_path_desc_fmt0 {int chpp; scalar_t__ desc; } ;
struct ccw_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_OSD (struct qeth_card*) ; 
 scalar_t__ IS_OSX (struct qeth_card*) ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int /*<<< orphan*/  QETH_CARD_TEXT_ (struct qeth_card*,int,char*,scalar_t__) ; 
 struct channel_path_desc_fmt0* ccw_device_get_chp_desc (struct ccw_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct channel_path_desc_fmt0*) ; 
 int qeth_osa_set_output_queues (struct qeth_card*,int) ; 

__attribute__((used)) static int qeth_update_from_chp_desc(struct qeth_card *card)
{
	struct ccw_device *ccwdev;
	struct channel_path_desc_fmt0 *chp_dsc;
	int rc = 0;

	QETH_CARD_TEXT(card, 2, "chp_desc");

	ccwdev = card->data.ccwdev;
	chp_dsc = ccw_device_get_chp_desc(ccwdev, 0);
	if (!chp_dsc)
		return -ENOMEM;

	card->info.func_level = 0x4100 + chp_dsc->desc;

	if (IS_OSD(card) || IS_OSX(card))
		/* CHPP field bit 6 == 1 -> single queue */
		rc = qeth_osa_set_output_queues(card, chp_dsc->chpp & 0x02);

	kfree(chp_dsc);
	QETH_CARD_TEXT_(card, 2, "nr:%x", card->qdio.no_out_queues);
	QETH_CARD_TEXT_(card, 2, "lvl:%02x", card->info.func_level);
	return rc;
}