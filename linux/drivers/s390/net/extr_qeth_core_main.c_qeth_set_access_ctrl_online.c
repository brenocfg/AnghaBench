#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ isolation; } ;
struct qeth_card {TYPE_1__* gdev; TYPE_2__ options; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_DEVID (struct qeth_card*) ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  IPA_SETADP_SET_ACCESS_CONTROL ; 
 scalar_t__ ISOLATION_MODE_NONE ; 
 scalar_t__ IS_OSD (struct qeth_card*) ; 
 scalar_t__ IS_OSX (struct qeth_card*) ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int /*<<< orphan*/  QETH_DBF_MESSAGE (int,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ qeth_adp_supported (struct qeth_card*,int /*<<< orphan*/ ) ; 
 int qeth_setadpparms_set_access_ctrl (struct qeth_card*,scalar_t__,int) ; 

int qeth_set_access_ctrl_online(struct qeth_card *card, int fallback)
{
	int rc = 0;

	QETH_CARD_TEXT(card, 4, "setactlo");

	if ((IS_OSD(card) || IS_OSX(card)) &&
	    qeth_adp_supported(card, IPA_SETADP_SET_ACCESS_CONTROL)) {
		rc = qeth_setadpparms_set_access_ctrl(card,
			card->options.isolation, fallback);
		if (rc) {
			QETH_DBF_MESSAGE(3, "IPA(SET_ACCESS_CTRL(%d) on device %x: sent failed\n",
					 rc, CARD_DEVID(card));
			rc = -EOPNOTSUPP;
		}
	} else if (card->options.isolation != ISOLATION_MODE_NONE) {
		card->options.isolation = ISOLATION_MODE_NONE;

		dev_err(&card->gdev->dev, "Adapter does not "
			"support QDIO data connection isolation\n");
		rc = -EOPNOTSUPP;
	}
	return rc;
}