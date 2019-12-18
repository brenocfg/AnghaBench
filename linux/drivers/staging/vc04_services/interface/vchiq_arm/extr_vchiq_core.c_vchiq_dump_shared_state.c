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
struct vchiq_state {int dummy; } ;
struct vchiq_slot_info {scalar_t__ use_count; scalar_t__ release_count; } ;
struct vchiq_shared_state {int slot_first; int slot_last; int* debug; int /*<<< orphan*/  slot_queue_recycle; int /*<<< orphan*/  tx_pos; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 size_t DEBUG_ENTRIES ; 
 struct vchiq_slot_info* SLOT_INFO_FROM_INDEX (struct vchiq_state*,int) ; 
 int scnprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  vchiq_dump (void*,char*,int) ; 

__attribute__((used)) static void
vchiq_dump_shared_state(void *dump_context, struct vchiq_state *state,
			struct vchiq_shared_state *shared, const char *label)
{
	static const char *const debug_names[] = {
		"<entries>",
		"SLOT_HANDLER_COUNT",
		"SLOT_HANDLER_LINE",
		"PARSE_LINE",
		"PARSE_HEADER",
		"PARSE_MSGID",
		"AWAIT_COMPLETION_LINE",
		"DEQUEUE_MESSAGE_LINE",
		"SERVICE_CALLBACK_LINE",
		"MSG_QUEUE_FULL_COUNT",
		"COMPLETION_QUEUE_FULL_COUNT"
	};
	int i;
	char buf[80];
	int len;

	len = scnprintf(buf, sizeof(buf),
		"  %s: slots %d-%d tx_pos=%x recycle=%x",
		label, shared->slot_first, shared->slot_last,
		shared->tx_pos, shared->slot_queue_recycle);
	vchiq_dump(dump_context, buf, len + 1);

	len = scnprintf(buf, sizeof(buf),
		"    Slots claimed:");
	vchiq_dump(dump_context, buf, len + 1);

	for (i = shared->slot_first; i <= shared->slot_last; i++) {
		struct vchiq_slot_info slot_info =
						*SLOT_INFO_FROM_INDEX(state, i);
		if (slot_info.use_count != slot_info.release_count) {
			len = scnprintf(buf, sizeof(buf),
				"      %d: %d/%d", i, slot_info.use_count,
				slot_info.release_count);
			vchiq_dump(dump_context, buf, len + 1);
		}
	}

	for (i = 1; i < shared->debug[DEBUG_ENTRIES]; i++) {
		len = scnprintf(buf, sizeof(buf), "    DEBUG: %s = %d(%x)",
			debug_names[i], shared->debug[i], shared->debug[i]);
		vchiq_dump(dump_context, buf, len + 1);
	}
}