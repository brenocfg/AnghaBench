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
struct gb_operation_msg_hdr {int type; int /*<<< orphan*/  operation_id; int /*<<< orphan*/  size; } ;
struct gb_connection {scalar_t__ state; int /*<<< orphan*/  name; TYPE_1__* hd; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  header ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 scalar_t__ GB_CONNECTION_STATE_DISABLED ; 
 int GB_MESSAGE_TYPE_RESPONSE ; 
 int /*<<< orphan*/  dev_err_ratelimited (struct device*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  dev_warn_ratelimited (struct device*,char*,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ gb_connection_is_offloaded (struct gb_connection*) ; 
 int /*<<< orphan*/  gb_connection_recv_request (struct gb_connection*,struct gb_operation_msg_hdr*,void*,size_t) ; 
 int /*<<< orphan*/  gb_connection_recv_response (struct gb_connection*,struct gb_operation_msg_hdr*,void*,size_t) ; 
 size_t le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct gb_operation_msg_hdr*,void*,int) ; 

void gb_connection_recv(struct gb_connection *connection,
			void *data, size_t size)
{
	struct gb_operation_msg_hdr header;
	struct device *dev = &connection->hd->dev;
	size_t msg_size;

	if (connection->state == GB_CONNECTION_STATE_DISABLED ||
	    gb_connection_is_offloaded(connection)) {
		dev_warn_ratelimited(dev, "%s: dropping %zu received bytes\n",
				     connection->name, size);
		return;
	}

	if (size < sizeof(header)) {
		dev_err_ratelimited(dev, "%s: short message received\n",
				    connection->name);
		return;
	}

	/* Use memcpy as data may be unaligned */
	memcpy(&header, data, sizeof(header));
	msg_size = le16_to_cpu(header.size);
	if (size < msg_size) {
		dev_err_ratelimited(dev,
				    "%s: incomplete message 0x%04x of type 0x%02x received (%zu < %zu)\n",
				    connection->name,
				    le16_to_cpu(header.operation_id),
				    header.type, size, msg_size);
		return;		/* XXX Should still complete operation */
	}

	if (header.type & GB_MESSAGE_TYPE_RESPONSE) {
		gb_connection_recv_response(connection,	&header, data,
					    msg_size);
	} else {
		gb_connection_recv_request(connection, &header, data,
					   msg_size);
	}
}