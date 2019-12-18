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
struct qeth_cmd_buffer {int /*<<< orphan*/  data; } ;
struct TYPE_4__ {int cula; scalar_t__ unit_addr2; } ;
struct TYPE_3__ {scalar_t__ ulp_filter_r; scalar_t__ ulp_connection_w; scalar_t__ cm_connection_r; } ;
struct qeth_card {TYPE_2__ info; TYPE_1__ token; } ;
struct ccw_dev_id {scalar_t__ devno; } ;
typedef  scalar_t__ __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_DDEV (struct qeth_card*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int QETH_MPC_TOKEN_LENGTH ; 
 int /*<<< orphan*/  QETH_ULP_SETUP_CONNECTION_TOKEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QETH_ULP_SETUP_CUA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QETH_ULP_SETUP_DEST_ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QETH_ULP_SETUP_FILTER_TOKEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QETH_ULP_SETUP_REAL_DEVADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ULP_SETUP ; 
 int /*<<< orphan*/  ULP_SETUP_SIZE ; 
 int /*<<< orphan*/  ccw_device_get_id (int /*<<< orphan*/ ,struct ccw_dev_id*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 struct qeth_cmd_buffer* qeth_mpc_alloc_cmd (struct qeth_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int qeth_send_control_data (struct qeth_card*,struct qeth_cmd_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qeth_ulp_setup_cb ; 

__attribute__((used)) static int qeth_ulp_setup(struct qeth_card *card)
{
	__u16 temp;
	struct qeth_cmd_buffer *iob;
	struct ccw_dev_id dev_id;

	QETH_CARD_TEXT(card, 2, "ulpsetup");

	iob = qeth_mpc_alloc_cmd(card, ULP_SETUP, ULP_SETUP_SIZE);
	if (!iob)
		return -ENOMEM;

	memcpy(QETH_ULP_SETUP_DEST_ADDR(iob->data),
	       &card->token.cm_connection_r, QETH_MPC_TOKEN_LENGTH);
	memcpy(QETH_ULP_SETUP_CONNECTION_TOKEN(iob->data),
	       &card->token.ulp_connection_w, QETH_MPC_TOKEN_LENGTH);
	memcpy(QETH_ULP_SETUP_FILTER_TOKEN(iob->data),
	       &card->token.ulp_filter_r, QETH_MPC_TOKEN_LENGTH);

	ccw_device_get_id(CARD_DDEV(card), &dev_id);
	memcpy(QETH_ULP_SETUP_CUA(iob->data), &dev_id.devno, 2);
	temp = (card->info.cula << 8) + card->info.unit_addr2;
	memcpy(QETH_ULP_SETUP_REAL_DEVADDR(iob->data), &temp, 2);
	return qeth_send_control_data(card, iob, qeth_ulp_setup_cb, NULL);
}