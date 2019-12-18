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
typedef  scalar_t__ u16 ;
struct qeth_cmd_buffer {int /*<<< orphan*/  data; struct qeth_channel* channel; } ;
struct qeth_channel {int /*<<< orphan*/  ccwdev; } ;
struct TYPE_4__ {scalar_t__* mcl_level; int /*<<< orphan*/  func_level; } ;
struct TYPE_3__ {scalar_t__ issuer_rm_r; } ;
struct qeth_card {TYPE_2__ info; TYPE_1__ token; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCW_DEVID (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int /*<<< orphan*/  QETH_DBF_MESSAGE (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  QETH_IDX_ACT_FUNC_LEVEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QETH_IDX_ACT_ISSUER_RM_TOKEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QETH_IDX_REPLY_LEVEL (int /*<<< orphan*/ ) ; 
 int QETH_MCL_LENGTH ; 
 int QETH_MPC_TOKEN_LENGTH ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int qeth_idx_check_activate_response (struct qeth_card*,struct qeth_channel*,struct qeth_cmd_buffer*) ; 
 int /*<<< orphan*/  qeth_notify_cmd (struct qeth_cmd_buffer*,int) ; 
 scalar_t__ qeth_peer_func_level (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_put_cmd (struct qeth_cmd_buffer*) ; 

__attribute__((used)) static void qeth_idx_activate_read_channel_cb(struct qeth_card *card,
					      struct qeth_cmd_buffer *iob,
					      unsigned int data_length)
{
	struct qeth_channel *channel = iob->channel;
	u16 peer_level;
	int rc;

	QETH_CARD_TEXT(card, 2, "idxrdcb");

	rc = qeth_idx_check_activate_response(card, channel, iob);
	if (rc)
		goto out;

	memcpy(&peer_level, QETH_IDX_ACT_FUNC_LEVEL(iob->data), 2);
	if (peer_level != qeth_peer_func_level(card->info.func_level)) {
		QETH_DBF_MESSAGE(2, "IDX_ACTIVATE on channel %x: function level mismatch (sent: %#x, received: %#x)\n",
				 CCW_DEVID(channel->ccwdev),
				 card->info.func_level, peer_level);
		rc = -EINVAL;
		goto out;
	}

	memcpy(&card->token.issuer_rm_r,
	       QETH_IDX_ACT_ISSUER_RM_TOKEN(iob->data),
	       QETH_MPC_TOKEN_LENGTH);
	memcpy(&card->info.mcl_level[0],
	       QETH_IDX_REPLY_LEVEL(iob->data), QETH_MCL_LENGTH);

out:
	qeth_notify_cmd(iob, rc);
	qeth_put_cmd(iob);
}