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
struct qeth_reply {scalar_t__ param; } ;
struct qeth_qoat_priv {int buffer_len; int response_len; int buffer; } ;
struct TYPE_4__ {int cmdlength; scalar_t__ seq_no; scalar_t__ used_total; } ;
struct TYPE_5__ {TYPE_1__ hdr; } ;
struct TYPE_6__ {TYPE_2__ setadapterparms; } ;
struct qeth_ipa_cmd {TYPE_3__ data; } ;
struct qeth_card {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int ENOSPC ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int /*<<< orphan*/  memcpy (int,char*,int) ; 
 scalar_t__ qeth_setadpparms_inspect_rc (struct qeth_ipa_cmd*) ; 

__attribute__((used)) static int qeth_setadpparms_query_oat_cb(struct qeth_card *card,
		struct qeth_reply *reply, unsigned long data)
{
	struct qeth_ipa_cmd *cmd = (struct qeth_ipa_cmd *)data;
	struct qeth_qoat_priv *priv;
	char *resdata;
	int resdatalen;

	QETH_CARD_TEXT(card, 3, "qoatcb");
	if (qeth_setadpparms_inspect_rc(cmd))
		return -EIO;

	priv = (struct qeth_qoat_priv *)reply->param;
	resdatalen = cmd->data.setadapterparms.hdr.cmdlength;
	resdata = (char *)data + 28;

	if (resdatalen > (priv->buffer_len - priv->response_len))
		return -ENOSPC;

	memcpy((priv->buffer + priv->response_len), resdata,
		resdatalen);
	priv->response_len += resdatalen;

	if (cmd->data.setadapterparms.hdr.seq_no <
	    cmd->data.setadapterparms.hdr.used_total)
		return 1;
	return 0;
}