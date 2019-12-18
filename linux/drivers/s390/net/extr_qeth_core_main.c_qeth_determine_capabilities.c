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
struct TYPE_5__ {int /*<<< orphan*/  cq; } ;
struct TYPE_6__ {int qfmt; int qdioac1; int qdioac2; int qdioac3; int icnt; } ;
struct qeth_card {TYPE_2__ options; TYPE_1__* gdev; TYPE_3__ ssqd; } ;
struct ccw_device {int /*<<< orphan*/  online; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct ccw_device* CARD_DDEV (struct qeth_card*) ; 
 int /*<<< orphan*/  CARD_DEVID (struct qeth_card*) ; 
 int CHSC_AC1_INITIATE_INPUTQ ; 
 int CHSC_AC3_FORMAT2_CQ_AVAILABLE ; 
 int QDIO_IQDIO_QFMT ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int /*<<< orphan*/  QETH_CARD_TEXT_ (struct qeth_card*,int,char*,int) ; 
 int /*<<< orphan*/  QETH_CQ_NOTAVAILABLE ; 
 int /*<<< orphan*/  QETH_DBF_MESSAGE (int,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ccw_device_set_offline (struct ccw_device*) ; 
 int ccw_device_set_online (struct ccw_device*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int qdio_get_ssqd_desc (struct ccw_device*,TYPE_3__*) ; 
 int qeth_read_conf_data (struct qeth_card*) ; 

__attribute__((used)) static void qeth_determine_capabilities(struct qeth_card *card)
{
	int rc;
	struct ccw_device *ddev;
	int ddev_offline = 0;

	QETH_CARD_TEXT(card, 2, "detcapab");
	ddev = CARD_DDEV(card);
	if (!ddev->online) {
		ddev_offline = 1;
		rc = ccw_device_set_online(ddev);
		if (rc) {
			QETH_CARD_TEXT_(card, 2, "3err%d", rc);
			goto out;
		}
	}

	rc = qeth_read_conf_data(card);
	if (rc) {
		QETH_DBF_MESSAGE(2, "qeth_read_conf_data on device %x returned %i\n",
				 CARD_DEVID(card), rc);
		QETH_CARD_TEXT_(card, 2, "5err%d", rc);
		goto out_offline;
	}

	rc = qdio_get_ssqd_desc(ddev, &card->ssqd);
	if (rc)
		QETH_CARD_TEXT_(card, 2, "6err%d", rc);

	QETH_CARD_TEXT_(card, 2, "qfmt%d", card->ssqd.qfmt);
	QETH_CARD_TEXT_(card, 2, "ac1:%02x", card->ssqd.qdioac1);
	QETH_CARD_TEXT_(card, 2, "ac2:%04x", card->ssqd.qdioac2);
	QETH_CARD_TEXT_(card, 2, "ac3:%04x", card->ssqd.qdioac3);
	QETH_CARD_TEXT_(card, 2, "icnt%d", card->ssqd.icnt);
	if (!((card->ssqd.qfmt != QDIO_IQDIO_QFMT) ||
	    ((card->ssqd.qdioac1 & CHSC_AC1_INITIATE_INPUTQ) == 0) ||
	    ((card->ssqd.qdioac3 & CHSC_AC3_FORMAT2_CQ_AVAILABLE) == 0))) {
		dev_info(&card->gdev->dev,
			"Completion Queueing supported\n");
	} else {
		card->options.cq = QETH_CQ_NOTAVAILABLE;
	}


out_offline:
	if (ddev_offline == 1)
		ccw_device_set_offline(ddev);
out:
	return;
}