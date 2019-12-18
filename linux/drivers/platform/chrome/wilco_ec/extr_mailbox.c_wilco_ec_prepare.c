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
struct wilco_ec_request {int data_size; scalar_t__ checksum; int /*<<< orphan*/  mailbox_version; int /*<<< orphan*/  mailbox_id; int /*<<< orphan*/  struct_version; } ;
struct wilco_ec_message {int request_size; struct wilco_ec_request* request_data; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  EC_MAILBOX_PROTO_VERSION ; 
 int /*<<< orphan*/  EC_MAILBOX_VERSION ; 
 int /*<<< orphan*/  memset (struct wilco_ec_request*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ wilco_ec_checksum (struct wilco_ec_request*,int) ; 

__attribute__((used)) static void wilco_ec_prepare(struct wilco_ec_message *msg,
			     struct wilco_ec_request *rq)
{
	memset(rq, 0, sizeof(*rq));
	rq->struct_version = EC_MAILBOX_PROTO_VERSION;
	rq->mailbox_id = msg->type;
	rq->mailbox_version = EC_MAILBOX_VERSION;
	rq->data_size = msg->request_size;

	/* Checksum header and data */
	rq->checksum = wilco_ec_checksum(rq, sizeof(*rq));
	rq->checksum += wilco_ec_checksum(msg->request_data, msg->request_size);
	rq->checksum = -rq->checksum;
}