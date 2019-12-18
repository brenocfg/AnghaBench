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
typedef  scalar_t__ u32 ;
struct controlvm_message_header {int dummy; } ;
struct TYPE_3__ {int failed; } ;
struct TYPE_4__ {scalar_t__ completion_status; TYPE_1__ flags; scalar_t__ payload_max_bytes; scalar_t__ payload_vm_offset; scalar_t__ payload_bytes; } ;
struct controlvm_message {TYPE_2__ hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (TYPE_2__*,struct controlvm_message_header*,int) ; 
 int /*<<< orphan*/  memset (struct controlvm_message*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void controlvm_init_response(struct controlvm_message *msg,
				    struct controlvm_message_header *msg_hdr,
				    int response)
{
	memset(msg, 0, sizeof(struct controlvm_message));
	memcpy(&msg->hdr, msg_hdr, sizeof(struct controlvm_message_header));
	msg->hdr.payload_bytes = 0;
	msg->hdr.payload_vm_offset = 0;
	msg->hdr.payload_max_bytes = 0;
	if (response < 0) {
		msg->hdr.flags.failed = 1;
		msg->hdr.completion_status = (u32)(-response);
	}
}