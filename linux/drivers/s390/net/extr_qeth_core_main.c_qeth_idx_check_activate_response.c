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
struct qeth_cmd_buffer {int /*<<< orphan*/  data; } ;
struct qeth_channel {TYPE_1__* ccwdev; } ;
struct qeth_card {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCW_DEVID (TYPE_1__*) ; 
 int EBUSY ; 
 int EIO ; 
 int EPERM ; 
 int /*<<< orphan*/  QETH_CARD_TEXT_ (struct qeth_card*,int,char*,int) ; 
 int /*<<< orphan*/  QETH_DBF_MESSAGE (int,char*,int /*<<< orphan*/ ) ; 
 int QETH_IDX_ACT_CAUSE_CODE (int /*<<< orphan*/ ) ; 
#define  QETH_IDX_ACT_ERR_AUTH 130 
#define  QETH_IDX_ACT_ERR_AUTH_USER 129 
#define  QETH_IDX_ACT_ERR_EXCL 128 
 scalar_t__ QETH_IS_IDX_ACT_POS_REPLY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int qeth_check_idx_response (struct qeth_card*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qeth_idx_check_activate_response(struct qeth_card *card,
					    struct qeth_channel *channel,
					    struct qeth_cmd_buffer *iob)
{
	int rc;

	rc = qeth_check_idx_response(card, iob->data);
	if (rc)
		return rc;

	if (QETH_IS_IDX_ACT_POS_REPLY(iob->data))
		return 0;

	/* negative reply: */
	QETH_CARD_TEXT_(card, 2, "idxneg%c",
			QETH_IDX_ACT_CAUSE_CODE(iob->data));

	switch (QETH_IDX_ACT_CAUSE_CODE(iob->data)) {
	case QETH_IDX_ACT_ERR_EXCL:
		dev_err(&channel->ccwdev->dev,
			"The adapter is used exclusively by another host\n");
		return -EBUSY;
	case QETH_IDX_ACT_ERR_AUTH:
	case QETH_IDX_ACT_ERR_AUTH_USER:
		dev_err(&channel->ccwdev->dev,
			"Setting the device online failed because of insufficient authorization\n");
		return -EPERM;
	default:
		QETH_DBF_MESSAGE(2, "IDX_ACTIVATE on channel %x: negative reply\n",
				 CCW_DEVID(channel->ccwdev));
		return -EIO;
	}
}