#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vchiq_state {int /*<<< orphan*/  sync_mutex; TYPE_2__* remote; int /*<<< orphan*/  slot_mutex; int /*<<< orphan*/  id; int /*<<< orphan*/  sync_release_event; struct vchiq_shared_state* local; } ;
struct vchiq_shared_state {int /*<<< orphan*/  slot_sync; int /*<<< orphan*/  sync_release; } ;
struct TYPE_3__ {int fourcc; } ;
struct vchiq_service {TYPE_1__ base; } ;
struct vchiq_header {int msgid; int size; int /*<<< orphan*/  data; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  VCHIQ_STATUS_T ;
struct TYPE_4__ {int /*<<< orphan*/  sync_trigger; } ;

/* Variables and functions */
 scalar_t__ SLOT_DATA_FROM_INDEX (struct vchiq_state*,int /*<<< orphan*/ ) ; 
 scalar_t__ SRVTRACE_ENABLED (struct vchiq_service*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VCHIQ_ERROR ; 
 int /*<<< orphan*/  VCHIQ_FOURCC_AS_4CHARS (int) ; 
 int /*<<< orphan*/  VCHIQ_LOG_INFO ; 
 scalar_t__ VCHIQ_LOG_TRACE ; 
 int VCHIQ_MAKE_FOURCC (char,char,char,char) ; 
 int VCHIQ_MSGID_PADDING ; 
 int /*<<< orphan*/  VCHIQ_MSG_DSTPORT (int) ; 
 scalar_t__ VCHIQ_MSG_PAUSE ; 
 scalar_t__ VCHIQ_MSG_RESUME ; 
 int /*<<< orphan*/  VCHIQ_MSG_SRCPORT (int) ; 
 scalar_t__ VCHIQ_MSG_TYPE (int) ; 
 int /*<<< orphan*/  VCHIQ_RETRY ; 
 int /*<<< orphan*/  VCHIQ_SERVICE_STATS_ADD (struct vchiq_service*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VCHIQ_SERVICE_STATS_INC (struct vchiq_service*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VCHIQ_STATS_INC (struct vchiq_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VCHIQ_SUCCESS ; 
 scalar_t__ copy_message_data (ssize_t (*) (void*,void*,size_t,size_t),void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ctrl_tx_bytes ; 
 int /*<<< orphan*/  ctrl_tx_count ; 
 int /*<<< orphan*/  error_count ; 
 int /*<<< orphan*/  min (size_t,size_t) ; 
 int /*<<< orphan*/  msg_type_str (scalar_t__) ; 
 scalar_t__ mutex_lock_killable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remote_event_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remote_event_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  vchiq_core_log_level ; 
 int /*<<< orphan*/  vchiq_log_dump_mem (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vchiq_log_error (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vchiq_log_info (scalar_t__,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vchiq_header*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vchiq_log_trace (scalar_t__,char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ vchiq_sync_log_level ; 

__attribute__((used)) static VCHIQ_STATUS_T
queue_message_sync(struct vchiq_state *state, struct vchiq_service *service,
		   int msgid,
		   ssize_t (*copy_callback)(void *context, void *dest,
					    size_t offset, size_t maxsize),
		   void *context, int size, int is_blocking)
{
	struct vchiq_shared_state *local;
	struct vchiq_header *header;
	ssize_t callback_result;

	local = state->local;

	if (VCHIQ_MSG_TYPE(msgid) != VCHIQ_MSG_RESUME &&
	    mutex_lock_killable(&state->sync_mutex))
		return VCHIQ_RETRY;

	remote_event_wait(&state->sync_release_event, &local->sync_release);

	rmb();

	header = (struct vchiq_header *)SLOT_DATA_FROM_INDEX(state,
		local->slot_sync);

	{
		int oldmsgid = header->msgid;

		if (oldmsgid != VCHIQ_MSGID_PADDING)
			vchiq_log_error(vchiq_core_log_level,
				"%d: qms - msgid %x, not PADDING",
				state->id, oldmsgid);
	}

	vchiq_log_info(vchiq_sync_log_level,
		       "%d: qms %s@%pK,%x (%d->%d)", state->id,
		       msg_type_str(VCHIQ_MSG_TYPE(msgid)),
		       header, size, VCHIQ_MSG_SRCPORT(msgid),
		       VCHIQ_MSG_DSTPORT(msgid));

	callback_result =
		copy_message_data(copy_callback, context,
				  header->data, size);

	if (callback_result < 0) {
		mutex_unlock(&state->slot_mutex);
		VCHIQ_SERVICE_STATS_INC(service,
					error_count);
		return VCHIQ_ERROR;
	}

	if (service) {
		if (SRVTRACE_ENABLED(service,
				     VCHIQ_LOG_INFO))
			vchiq_log_dump_mem("Sent", 0,
					   header->data,
					   min((size_t)16,
					       (size_t)callback_result));

		VCHIQ_SERVICE_STATS_INC(service, ctrl_tx_count);
		VCHIQ_SERVICE_STATS_ADD(service, ctrl_tx_bytes, size);
	} else {
		VCHIQ_STATS_INC(state, ctrl_tx_count);
	}

	header->size = size;
	header->msgid = msgid;

	if (vchiq_sync_log_level >= VCHIQ_LOG_TRACE) {
		int svc_fourcc;

		svc_fourcc = service
			? service->base.fourcc
			: VCHIQ_MAKE_FOURCC('?', '?', '?', '?');

		vchiq_log_trace(vchiq_sync_log_level,
			"Sent Sync Msg %s(%u) to %c%c%c%c s:%u d:%d len:%d",
			msg_type_str(VCHIQ_MSG_TYPE(msgid)),
			VCHIQ_MSG_TYPE(msgid),
			VCHIQ_FOURCC_AS_4CHARS(svc_fourcc),
			VCHIQ_MSG_SRCPORT(msgid),
			VCHIQ_MSG_DSTPORT(msgid),
			size);
	}

	remote_event_signal(&state->remote->sync_trigger);

	if (VCHIQ_MSG_TYPE(msgid) != VCHIQ_MSG_PAUSE)
		mutex_unlock(&state->sync_mutex);

	return VCHIQ_SUCCESS;
}