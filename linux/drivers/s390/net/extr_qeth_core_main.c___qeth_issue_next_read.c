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
struct qeth_cmd_buffer {int /*<<< orphan*/  callback; int /*<<< orphan*/  data; int /*<<< orphan*/  length; struct qeth_channel* channel; } ;
struct qeth_channel {scalar_t__ state; int /*<<< orphan*/  irq_pending; int /*<<< orphan*/  ccwdev; } ;
struct qeth_card {int read_or_write_problem; int /*<<< orphan*/  wait_q; struct qeth_cmd_buffer* read_cmd; } ;
struct ccw1 {int dummy; } ;
typedef  int /*<<< orphan*/  addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_DEVID (struct qeth_card*) ; 
 int /*<<< orphan*/  CCW_CMD_READ ; 
 scalar_t__ CH_STATE_UP ; 
 int EIO ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int /*<<< orphan*/  QETH_DBF_MESSAGE (int,char*,int,int /*<<< orphan*/ ) ; 
 struct ccw1* __ccw_from_cmd (struct qeth_cmd_buffer*) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ccw_device_start (int /*<<< orphan*/ ,struct ccw1*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_get_cmd (struct qeth_cmd_buffer*) ; 
 int /*<<< orphan*/  qeth_issue_next_read_cb ; 
 int /*<<< orphan*/  qeth_put_cmd (struct qeth_cmd_buffer*) ; 
 int /*<<< orphan*/  qeth_schedule_recovery (struct qeth_card*) ; 
 int /*<<< orphan*/  qeth_setup_ccw (struct ccw1*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __qeth_issue_next_read(struct qeth_card *card)
{
	struct qeth_cmd_buffer *iob = card->read_cmd;
	struct qeth_channel *channel = iob->channel;
	struct ccw1 *ccw = __ccw_from_cmd(iob);
	int rc;

	QETH_CARD_TEXT(card, 5, "issnxrd");
	if (channel->state != CH_STATE_UP)
		return -EIO;

	memset(iob->data, 0, iob->length);
	qeth_setup_ccw(ccw, CCW_CMD_READ, 0, iob->length, iob->data);
	iob->callback = qeth_issue_next_read_cb;
	/* keep the cmd alive after completion: */
	qeth_get_cmd(iob);

	QETH_CARD_TEXT(card, 6, "noirqpnd");
	rc = ccw_device_start(channel->ccwdev, ccw, (addr_t) iob, 0, 0);
	if (rc) {
		QETH_DBF_MESSAGE(2, "error %i on device %x when starting next read ccw!\n",
				 rc, CARD_DEVID(card));
		atomic_set(&channel->irq_pending, 0);
		qeth_put_cmd(iob);
		card->read_or_write_problem = 1;
		qeth_schedule_recovery(card);
		wake_up(&card->wait_q);
	}
	return rc;
}