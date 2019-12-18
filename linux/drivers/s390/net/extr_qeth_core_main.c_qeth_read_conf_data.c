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
struct qeth_node_desc {int dummy; } ;
struct qeth_cmd_buffer {int /*<<< orphan*/  data; int /*<<< orphan*/  length; int /*<<< orphan*/  callback; } ;
struct qeth_channel {int /*<<< orphan*/  ccwdev; } ;
struct qeth_card {struct qeth_channel data; } ;
struct ciw {scalar_t__ cmd; int count; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIW_TYPE_RCD ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  QETH_RCD_TIMEOUT ; 
 int /*<<< orphan*/  __ccw_from_cmd (struct qeth_cmd_buffer*) ; 
 struct ciw* ccw_device_get_ciw (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct qeth_cmd_buffer* qeth_alloc_cmd (struct qeth_channel*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_read_conf_data_cb ; 
 int qeth_send_control_data (struct qeth_card*,struct qeth_cmd_buffer*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qeth_setup_ccw (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qeth_read_conf_data(struct qeth_card *card)
{
	struct qeth_channel *channel = &card->data;
	struct qeth_cmd_buffer *iob;
	struct ciw *ciw;

	/* scan for RCD command in extended SenseID data */
	ciw = ccw_device_get_ciw(channel->ccwdev, CIW_TYPE_RCD);
	if (!ciw || ciw->cmd == 0)
		return -EOPNOTSUPP;
	if (ciw->count < sizeof(struct qeth_node_desc))
		return -EINVAL;

	iob = qeth_alloc_cmd(channel, ciw->count, 1, QETH_RCD_TIMEOUT);
	if (!iob)
		return -ENOMEM;

	iob->callback = qeth_read_conf_data_cb;
	qeth_setup_ccw(__ccw_from_cmd(iob), ciw->cmd, 0, iob->length,
		       iob->data);

	return qeth_send_control_data(card, iob, NULL, NULL);
}