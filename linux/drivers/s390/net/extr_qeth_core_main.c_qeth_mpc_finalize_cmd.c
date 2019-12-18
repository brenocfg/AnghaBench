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
struct qeth_cmd_buffer {int /*<<< orphan*/  callback; int /*<<< orphan*/  data; } ;
struct TYPE_2__ {int /*<<< orphan*/  pdu_hdr_ack; int /*<<< orphan*/  pdu_hdr; } ;
struct qeth_card {TYPE_1__ seqno; } ;

/* Variables and functions */
 int /*<<< orphan*/  QETH_PDU_HEADER_ACK_SEQ_NO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QETH_PDU_HEADER_SEQ_NO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QETH_SEQ_NO_LENGTH ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_idx_finalize_cmd (struct qeth_card*,struct qeth_cmd_buffer*) ; 
 int /*<<< orphan*/  qeth_release_buffer_cb ; 

__attribute__((used)) static void qeth_mpc_finalize_cmd(struct qeth_card *card,
				  struct qeth_cmd_buffer *iob)
{
	qeth_idx_finalize_cmd(card, iob);

	memcpy(QETH_PDU_HEADER_SEQ_NO(iob->data),
	       &card->seqno.pdu_hdr, QETH_SEQ_NO_LENGTH);
	card->seqno.pdu_hdr++;
	memcpy(QETH_PDU_HEADER_ACK_SEQ_NO(iob->data),
	       &card->seqno.pdu_hdr_ack, QETH_SEQ_NO_LENGTH);

	iob->callback = qeth_release_buffer_cb;
}