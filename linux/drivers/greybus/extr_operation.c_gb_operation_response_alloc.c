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
typedef  int u8 ;
struct gb_operation_msg_hdr {int /*<<< orphan*/  operation_id; } ;
struct gb_operation {int type; struct gb_message* response; TYPE_1__* request; TYPE_3__* connection; } ;
struct gb_message {TYPE_2__* header; struct gb_operation* operation; } ;
struct gb_host_device {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_6__ {struct gb_host_device* hd; } ;
struct TYPE_5__ {int /*<<< orphan*/  operation_id; } ;
struct TYPE_4__ {struct gb_operation_msg_hdr* header; } ;

/* Variables and functions */
 int GB_MESSAGE_TYPE_RESPONSE ; 
 struct gb_message* gb_operation_message_alloc (struct gb_host_device*,int,size_t,int /*<<< orphan*/ ) ; 

bool gb_operation_response_alloc(struct gb_operation *operation,
				 size_t response_size, gfp_t gfp)
{
	struct gb_host_device *hd = operation->connection->hd;
	struct gb_operation_msg_hdr *request_header;
	struct gb_message *response;
	u8 type;

	type = operation->type | GB_MESSAGE_TYPE_RESPONSE;
	response = gb_operation_message_alloc(hd, type, response_size, gfp);
	if (!response)
		return false;
	response->operation = operation;

	/*
	 * Size and type get initialized when the message is
	 * allocated.  The errno will be set before sending.  All
	 * that's left is the operation id, which we copy from the
	 * request message header (as-is, in little-endian order).
	 */
	request_header = operation->request->header;
	response->header->operation_id = request_header->operation_id;
	operation->response = response;

	return true;
}