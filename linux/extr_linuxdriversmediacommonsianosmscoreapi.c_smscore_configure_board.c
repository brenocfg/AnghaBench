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
struct smscore_device_t {int /*<<< orphan*/  context; int /*<<< orphan*/  (* sendrequest_handler ) (int /*<<< orphan*/ ,struct sms_msg_data*,int) ;int /*<<< orphan*/  board_id; } ;
struct TYPE_2__ {int msg_length; int /*<<< orphan*/  msg_type; scalar_t__ msg_flags; int /*<<< orphan*/  msg_dst_id; scalar_t__ msg_src_id; } ;
struct sms_msg_data {scalar_t__* msg_data; TYPE_1__ x_msg_header; } ;
struct sms_board {scalar_t__ crystal; scalar_t__ mtu; } ;
typedef  int /*<<< orphan*/  mtu_msg ;
typedef  int /*<<< orphan*/  crys_msg ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HIF_TASK ; 
 int /*<<< orphan*/  MSG_SMS_NEW_CRYSTAL_REQ ; 
 int /*<<< orphan*/  MSG_SMS_SET_MAX_TX_MSG_LEN_REQ ; 
 int /*<<< orphan*/  SMS_INIT_MSG (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 struct sms_board* sms_get_board (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct sms_msg_data*,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,struct sms_msg_data*,int) ; 

__attribute__((used)) static int smscore_configure_board(struct smscore_device_t *coredev)
{
	struct sms_board *board;

	board = sms_get_board(coredev->board_id);
	if (!board) {
		pr_err("no board configuration exist.\n");
		return -EINVAL;
	}

	if (board->mtu) {
		struct sms_msg_data mtu_msg;
		pr_debug("set max transmit unit %d\n", board->mtu);

		mtu_msg.x_msg_header.msg_src_id = 0;
		mtu_msg.x_msg_header.msg_dst_id = HIF_TASK;
		mtu_msg.x_msg_header.msg_flags = 0;
		mtu_msg.x_msg_header.msg_type = MSG_SMS_SET_MAX_TX_MSG_LEN_REQ;
		mtu_msg.x_msg_header.msg_length = sizeof(mtu_msg);
		mtu_msg.msg_data[0] = board->mtu;

		coredev->sendrequest_handler(coredev->context, &mtu_msg,
					     sizeof(mtu_msg));
	}

	if (board->crystal) {
		struct sms_msg_data crys_msg;
		pr_debug("set crystal value %d\n", board->crystal);

		SMS_INIT_MSG(&crys_msg.x_msg_header,
				MSG_SMS_NEW_CRYSTAL_REQ,
				sizeof(crys_msg));
		crys_msg.msg_data[0] = board->crystal;

		coredev->sendrequest_handler(coredev->context, &crys_msg,
					     sizeof(crys_msg));
	}

	return 0;
}