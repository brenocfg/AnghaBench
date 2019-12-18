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
struct wilco_ec_message {int request_size; int response_size; struct ec_property_response* response_data; struct ec_property_request* request_data; int /*<<< orphan*/  type; } ;
struct wilco_ec_device {int dummy; } ;
struct ec_property_response {scalar_t__ op; int /*<<< orphan*/  property_id; } ;
struct ec_property_request {scalar_t__ op; int /*<<< orphan*/  property_id; } ;
typedef  int /*<<< orphan*/  ec_msg ;

/* Variables and functions */
 int EBADMSG ; 
 int /*<<< orphan*/  WILCO_EC_MSG_PROPERTY ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct wilco_ec_message*,int /*<<< orphan*/ ,int) ; 
 int wilco_ec_mailbox (struct wilco_ec_device*,struct wilco_ec_message*) ; 

__attribute__((used)) static int send_property_msg(struct wilco_ec_device *ec,
			     struct ec_property_request *rq,
			     struct ec_property_response *rs)
{
	struct wilco_ec_message ec_msg;
	int ret;

	memset(&ec_msg, 0, sizeof(ec_msg));
	ec_msg.type = WILCO_EC_MSG_PROPERTY;
	ec_msg.request_data = rq;
	ec_msg.request_size = sizeof(*rq);
	ec_msg.response_data = rs;
	ec_msg.response_size = sizeof(*rs);

	ret = wilco_ec_mailbox(ec, &ec_msg);
	if (ret < 0)
		return ret;
	if (rs->op != rq->op)
		return -EBADMSG;
	if (memcmp(rq->property_id, rs->property_id, sizeof(rs->property_id)))
		return -EBADMSG;

	return 0;
}