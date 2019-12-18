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
struct wilco_ec_property_msg {int /*<<< orphan*/  length; int /*<<< orphan*/  data; int /*<<< orphan*/  property_id; } ;
struct wilco_ec_device {int dummy; } ;
struct ec_property_response {int /*<<< orphan*/  length; } ;
struct ec_property_request {int /*<<< orphan*/  data; int /*<<< orphan*/  length; int /*<<< orphan*/  property_id; int /*<<< orphan*/  op; } ;
typedef  int /*<<< orphan*/  rq ;

/* Variables and functions */
 int EBADMSG ; 
 int /*<<< orphan*/  EC_OP_SET ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ec_property_request*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_unaligned_le32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int send_property_msg (struct wilco_ec_device*,struct ec_property_request*,struct ec_property_response*) ; 

int wilco_ec_set_property(struct wilco_ec_device *ec,
			  struct wilco_ec_property_msg *prop_msg)
{
	struct ec_property_request rq;
	struct ec_property_response rs;
	int ret;

	memset(&rq, 0, sizeof(rq));
	rq.op = EC_OP_SET;
	put_unaligned_le32(prop_msg->property_id, rq.property_id);
	rq.length = prop_msg->length;
	memcpy(rq.data, prop_msg->data, prop_msg->length);

	ret = send_property_msg(ec, &rq, &rs);
	if (ret < 0)
		return ret;
	if (rs.length != prop_msg->length)
		return -EBADMSG;

	return 0;
}