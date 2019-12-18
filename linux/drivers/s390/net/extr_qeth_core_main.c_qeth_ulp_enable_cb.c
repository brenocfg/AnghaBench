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
struct qeth_reply {scalar_t__ param; } ;
struct qeth_cmd_buffer {int /*<<< orphan*/  data; } ;
struct TYPE_4__ {scalar_t__ link_type; } ;
struct TYPE_3__ {scalar_t__ ulp_filter_r; } ;
struct qeth_card {TYPE_2__ info; TYPE_1__ token; } ;
typedef  scalar_t__ __u8 ;
typedef  scalar_t__ __u16 ;

/* Variables and functions */
 scalar_t__ IS_IQD (struct qeth_card*) ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int /*<<< orphan*/  QETH_CARD_TEXT_ (struct qeth_card*,int,char*,scalar_t__) ; 
 scalar_t__ QETH_MPC_DIFINFO_LEN_INDICATES_LINK_TYPE ; 
 int QETH_MPC_TOKEN_LENGTH ; 
 scalar_t__ QETH_ULP_ENABLE_RESP_DIFINFO_LEN (int /*<<< orphan*/ ) ; 
 scalar_t__ QETH_ULP_ENABLE_RESP_FILTER_TOKEN (int /*<<< orphan*/ ) ; 
 scalar_t__ QETH_ULP_ENABLE_RESP_LINK_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ QETH_ULP_ENABLE_RESP_MAX_MTU (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__,int) ; 
 scalar_t__ qeth_get_mtu_outof_framesize (scalar_t__) ; 

__attribute__((used)) static int qeth_ulp_enable_cb(struct qeth_card *card, struct qeth_reply *reply,
		unsigned long data)
{
	__u16 mtu, framesize;
	__u16 len;
	__u8 link_type;
	struct qeth_cmd_buffer *iob;

	QETH_CARD_TEXT(card, 2, "ulpenacb");

	iob = (struct qeth_cmd_buffer *) data;
	memcpy(&card->token.ulp_filter_r,
	       QETH_ULP_ENABLE_RESP_FILTER_TOKEN(iob->data),
	       QETH_MPC_TOKEN_LENGTH);
	if (IS_IQD(card)) {
		memcpy(&framesize, QETH_ULP_ENABLE_RESP_MAX_MTU(iob->data), 2);
		mtu = qeth_get_mtu_outof_framesize(framesize);
	} else {
		mtu = *(__u16 *)QETH_ULP_ENABLE_RESP_MAX_MTU(iob->data);
	}
	*(u16 *)reply->param = mtu;

	memcpy(&len, QETH_ULP_ENABLE_RESP_DIFINFO_LEN(iob->data), 2);
	if (len >= QETH_MPC_DIFINFO_LEN_INDICATES_LINK_TYPE) {
		memcpy(&link_type,
		       QETH_ULP_ENABLE_RESP_LINK_TYPE(iob->data), 1);
		card->info.link_type = link_type;
	} else
		card->info.link_type = 0;
	QETH_CARD_TEXT_(card, 2, "link%d", card->info.link_type);
	return 0;
}