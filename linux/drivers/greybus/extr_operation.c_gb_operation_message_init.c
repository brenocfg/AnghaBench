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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct gb_operation_msg_hdr {scalar_t__ result; scalar_t__ type; scalar_t__ operation_id; int /*<<< orphan*/  size; } ;
struct gb_message {size_t payload_size; struct gb_operation_msg_hdr* payload; struct gb_operation_msg_hdr* header; struct gb_operation_msg_hdr* buffer; } ;
struct gb_host_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ GB_REQUEST_TYPE_INVALID ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gb_operation_message_init(struct gb_host_device *hd,
				      struct gb_message *message,
				      u16 operation_id,
				      size_t payload_size, u8 type)
{
	struct gb_operation_msg_hdr *header;

	header = message->buffer;

	message->header = header;
	message->payload = payload_size ? header + 1 : NULL;
	message->payload_size = payload_size;

	/*
	 * The type supplied for incoming message buffers will be
	 * GB_REQUEST_TYPE_INVALID. Such buffers will be overwritten by
	 * arriving data so there's no need to initialize the message header.
	 */
	if (type != GB_REQUEST_TYPE_INVALID) {
		u16 message_size = (u16)(sizeof(*header) + payload_size);

		/*
		 * For a request, the operation id gets filled in
		 * when the message is sent.  For a response, it
		 * will be copied from the request by the caller.
		 *
		 * The result field in a request message must be
		 * zero.  It will be set just prior to sending for
		 * a response.
		 */
		header->size = cpu_to_le16(message_size);
		header->operation_id = 0;
		header->type = type;
		header->result = 0;
	}
}