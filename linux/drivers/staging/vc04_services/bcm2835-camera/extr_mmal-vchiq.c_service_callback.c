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
typedef  int /*<<< orphan*/  u32 ;
struct vchiq_mmal_instance {int /*<<< orphan*/  handle; } ;
struct vchi_held_msg {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  cmplt; int /*<<< orphan*/  msg_len; struct mmal_msg* msg; struct vchi_held_msg msg_handle; } ;
struct TYPE_6__ {TYPE_2__ sync; } ;
struct mmal_msg_context {TYPE_3__ u; } ;
struct TYPE_4__ {int const context; int /*<<< orphan*/  type; } ;
struct mmal_msg {TYPE_1__ h; } ;
typedef  int VCHI_CALLBACK_REASON_T ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_DUMP_MSG (struct mmal_msg*,int /*<<< orphan*/ ,char*) ; 
#define  MMAL_MSG_TYPE_BUFFER_FROM_HOST 134 
#define  MMAL_MSG_TYPE_BUFFER_TO_HOST 133 
#define  MMAL_MSG_TYPE_EVENT_TO_HOST 132 
#define  VCHI_CALLBACK_BULK_RECEIVED 131 
#define  VCHI_CALLBACK_BULK_RECEIVE_ABORTED 130 
#define  VCHI_CALLBACK_MSG_AVAILABLE 129 
#define  VCHI_CALLBACK_SERVICE_CLOSED 128 
 int /*<<< orphan*/  VCHI_FLAGS_NONE ; 
 int /*<<< orphan*/  buffer_to_host_cb (struct vchiq_mmal_instance*,struct mmal_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bulk_abort_cb (struct vchiq_mmal_instance*,void*) ; 
 int /*<<< orphan*/  bulk_receive_cb (struct vchiq_mmal_instance*,void*) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_to_host_cb (struct vchiq_mmal_instance*,struct mmal_msg*,int /*<<< orphan*/ ) ; 
 struct mmal_msg_context* lookup_msg_context (struct vchiq_mmal_instance*,int const) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  vchi_held_msg_release (struct vchi_held_msg*) ; 
 int vchi_msg_hold (int /*<<< orphan*/ ,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct vchi_held_msg*) ; 

__attribute__((used)) static void service_callback(void *param,
			     const VCHI_CALLBACK_REASON_T reason,
			     void *bulk_ctx)
{
	struct vchiq_mmal_instance *instance = param;
	int status;
	u32 msg_len;
	struct mmal_msg *msg;
	struct vchi_held_msg msg_handle;
	struct mmal_msg_context *msg_context;

	if (!instance) {
		pr_err("Message callback passed NULL instance\n");
		return;
	}

	switch (reason) {
	case VCHI_CALLBACK_MSG_AVAILABLE:
		status = vchi_msg_hold(instance->handle, (void **)&msg,
				       &msg_len, VCHI_FLAGS_NONE, &msg_handle);
		if (status) {
			pr_err("Unable to dequeue a message (%d)\n", status);
			break;
		}

		DBG_DUMP_MSG(msg, msg_len, "<<< reply message");

		/* handling is different for buffer messages */
		switch (msg->h.type) {
		case MMAL_MSG_TYPE_BUFFER_FROM_HOST:
			vchi_held_msg_release(&msg_handle);
			break;

		case MMAL_MSG_TYPE_EVENT_TO_HOST:
			event_to_host_cb(instance, msg, msg_len);
			vchi_held_msg_release(&msg_handle);

			break;

		case MMAL_MSG_TYPE_BUFFER_TO_HOST:
			buffer_to_host_cb(instance, msg, msg_len);
			vchi_held_msg_release(&msg_handle);
			break;

		default:
			/* messages dependent on header context to complete */
			if (!msg->h.context) {
				pr_err("received message context was null!\n");
				vchi_held_msg_release(&msg_handle);
				break;
			}

			msg_context = lookup_msg_context(instance,
							 msg->h.context);
			if (!msg_context) {
				pr_err("received invalid message context %u!\n",
				       msg->h.context);
				vchi_held_msg_release(&msg_handle);
				break;
			}

			/* fill in context values */
			msg_context->u.sync.msg_handle = msg_handle;
			msg_context->u.sync.msg = msg;
			msg_context->u.sync.msg_len = msg_len;

			/* todo: should this check (completion_done()
			 * == 1) for no one waiting? or do we need a
			 * flag to tell us the completion has been
			 * interrupted so we can free the message and
			 * its context. This probably also solves the
			 * message arriving after interruption todo
			 * below
			 */

			/* complete message so caller knows it happened */
			complete(&msg_context->u.sync.cmplt);
			break;
		}

		break;

	case VCHI_CALLBACK_BULK_RECEIVED:
		bulk_receive_cb(instance, bulk_ctx);
		break;

	case VCHI_CALLBACK_BULK_RECEIVE_ABORTED:
		bulk_abort_cb(instance, bulk_ctx);
		break;

	case VCHI_CALLBACK_SERVICE_CLOSED:
		/* TODO: consider if this requires action if received when
		 * driver is not explicitly closing the service
		 */
		break;

	default:
		pr_err("Received unhandled message reason %d\n", reason);
		break;
	}
}