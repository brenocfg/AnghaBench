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
struct wilco_ec_request {int dummy; } ;
struct wilco_ec_message {int /*<<< orphan*/  request_size; int /*<<< orphan*/  response_size; int /*<<< orphan*/  flags; int /*<<< orphan*/  type; } ;
struct wilco_ec_device {int /*<<< orphan*/  mailbox_lock; struct wilco_ec_request* data_buffer; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wilco_ec_prepare (struct wilco_ec_message*,struct wilco_ec_request*) ; 
 int wilco_ec_transfer (struct wilco_ec_device*,struct wilco_ec_message*,struct wilco_ec_request*) ; 

int wilco_ec_mailbox(struct wilco_ec_device *ec, struct wilco_ec_message *msg)
{
	struct wilco_ec_request *rq;
	int ret;

	dev_dbg(ec->dev, "type=%04x flags=%02x rslen=%zu rqlen=%zu\n",
		msg->type, msg->flags, msg->response_size, msg->request_size);

	mutex_lock(&ec->mailbox_lock);
	/* Prepare request packet */
	rq = ec->data_buffer;
	wilco_ec_prepare(msg, rq);

	ret = wilco_ec_transfer(ec, msg, rq);
	mutex_unlock(&ec->mailbox_lock);

	return ret;

}