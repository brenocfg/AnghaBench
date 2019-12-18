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
typedef  union hv_connection_id {int dummy; } hv_connection_id ;
typedef  int u64 ;
struct hv_per_cpu_context {struct hv_input_post_message* post_msg_page; } ;
struct hv_input_post_message {int message_type; size_t payload_size; scalar_t__ payload; scalar_t__ reserved; union hv_connection_id connectionid; } ;
typedef  enum hv_message_type { ____Placeholder_hv_message_type } hv_message_type ;
struct TYPE_2__ {int /*<<< orphan*/  cpu_context; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  HVCALL_POST_MESSAGE ; 
 size_t HV_MESSAGE_PAYLOAD_BYTE_COUNT ; 
 struct hv_per_cpu_context* get_cpu_ptr (int /*<<< orphan*/ ) ; 
 TYPE_1__ hv_context ; 
 int hv_do_hypercall (int /*<<< orphan*/ ,struct hv_input_post_message*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 
 int /*<<< orphan*/  put_cpu_ptr (struct hv_per_cpu_context*) ; 

int hv_post_message(union hv_connection_id connection_id,
		  enum hv_message_type message_type,
		  void *payload, size_t payload_size)
{
	struct hv_input_post_message *aligned_msg;
	struct hv_per_cpu_context *hv_cpu;
	u64 status;

	if (payload_size > HV_MESSAGE_PAYLOAD_BYTE_COUNT)
		return -EMSGSIZE;

	hv_cpu = get_cpu_ptr(hv_context.cpu_context);
	aligned_msg = hv_cpu->post_msg_page;
	aligned_msg->connectionid = connection_id;
	aligned_msg->reserved = 0;
	aligned_msg->message_type = message_type;
	aligned_msg->payload_size = payload_size;
	memcpy((void *)aligned_msg->payload, payload, payload_size);

	status = hv_do_hypercall(HVCALL_POST_MESSAGE, aligned_msg, NULL);

	/* Preemption must remain disabled until after the hypercall
	 * so some other thread can't get scheduled onto this cpu and
	 * corrupt the per-cpu post_msg_page
	 */
	put_cpu_ptr(hv_cpu);

	return status & 0xFFFF;
}