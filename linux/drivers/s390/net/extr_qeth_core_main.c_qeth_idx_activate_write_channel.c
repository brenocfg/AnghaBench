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
struct qeth_cmd_buffer {int /*<<< orphan*/  callback; int /*<<< orphan*/  data; } ;
struct qeth_channel {int /*<<< orphan*/  state; } ;
struct qeth_card {struct qeth_channel write; } ;

/* Variables and functions */
 int /*<<< orphan*/  CH_STATE_UP ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IDX_ACTIVATE_SIZE ; 
 int /*<<< orphan*/  IDX_ACTIVATE_WRITE ; 
 int /*<<< orphan*/  QETH_BUFSIZE ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int /*<<< orphan*/  QETH_TIMEOUT ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct qeth_cmd_buffer* qeth_alloc_cmd (struct qeth_channel*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_idx_activate_write_channel_cb ; 
 int /*<<< orphan*/  qeth_idx_setup_activate_cmd (struct qeth_card*,struct qeth_cmd_buffer*) ; 
 int qeth_send_control_data (struct qeth_card*,struct qeth_cmd_buffer*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qeth_idx_activate_write_channel(struct qeth_card *card)
{
	struct qeth_channel *channel = &card->write;
	struct qeth_cmd_buffer *iob;
	int rc;

	QETH_CARD_TEXT(card, 2, "idxwrite");

	iob = qeth_alloc_cmd(channel, QETH_BUFSIZE, 2, QETH_TIMEOUT);
	if (!iob)
		return -ENOMEM;

	memcpy(iob->data, IDX_ACTIVATE_WRITE, IDX_ACTIVATE_SIZE);
	qeth_idx_setup_activate_cmd(card, iob);
	iob->callback = qeth_idx_activate_write_channel_cb;

	rc = qeth_send_control_data(card, iob, NULL, NULL);
	if (rc)
		return rc;

	channel->state = CH_STATE_UP;
	return 0;
}