#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct vchiq_mmal_instance {int dummy; } ;
struct TYPE_13__ {unsigned long buffer_used; int /*<<< orphan*/  buffer_to_host_work; int /*<<< orphan*/  pts; int /*<<< orphan*/  dts; TYPE_1__* buffer; } ;
struct TYPE_14__ {TYPE_6__ bulk; } ;
struct mmal_msg_context {TYPE_7__ u; TYPE_5__* instance; } ;
struct TYPE_9__ {unsigned long length; int /*<<< orphan*/  pts; int /*<<< orphan*/  dts; } ;
struct TYPE_10__ {TYPE_2__ buffer_header; } ;
struct TYPE_11__ {TYPE_3__ buffer_from_host; } ;
struct mmal_msg {TYPE_4__ u; } ;
struct TYPE_12__ {int /*<<< orphan*/  bulk_wq; } ;
struct TYPE_8__ {unsigned long buffer_size; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bulk_receive(struct vchiq_mmal_instance *instance,
			struct mmal_msg *msg,
			struct mmal_msg_context *msg_context)
{
	unsigned long rd_len;

	rd_len = msg->u.buffer_from_host.buffer_header.length;

	if (!msg_context->u.bulk.buffer) {
		pr_err("bulk.buffer not configured - error in buffer_from_host\n");

		/* todo: this is a serious error, we should never have
		 * committed a buffer_to_host operation to the mmal
		 * port without the buffer to back it up (underflow
		 * handling) and there is no obvious way to deal with
		 * this - how is the mmal servie going to react when
		 * we fail to do the xfer and reschedule a buffer when
		 * it arrives? perhaps a starved flag to indicate a
		 * waiting bulk receive?
		 */

		return -EINVAL;
	}

	/* ensure we do not overrun the available buffer */
	if (rd_len > msg_context->u.bulk.buffer->buffer_size) {
		rd_len = msg_context->u.bulk.buffer->buffer_size;
		pr_warn("short read as not enough receive buffer space\n");
		/* todo: is this the correct response, what happens to
		 * the rest of the message data?
		 */
	}

	/* store length */
	msg_context->u.bulk.buffer_used = rd_len;
	msg_context->u.bulk.dts = msg->u.buffer_from_host.buffer_header.dts;
	msg_context->u.bulk.pts = msg->u.buffer_from_host.buffer_header.pts;

	queue_work(msg_context->instance->bulk_wq,
		   &msg_context->u.bulk.buffer_to_host_work);

	return 0;
}