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
struct TYPE_4__ {int /*<<< orphan*/  (* submit_command ) (struct ctlr_info*,struct CommandList*) ;} ;
struct ctlr_info {int* reply_map; TYPE_2__ access; scalar_t__ vaddr; int /*<<< orphan*/  commands_outstanding; } ;
struct CommandList {int cmd_type; int /*<<< orphan*/  busaddr; TYPE_1__* device; } ;
struct TYPE_3__ {int /*<<< orphan*/  commands_outstanding; } ;

/* Variables and functions */
#define  CMD_IOACCEL1 130 
#define  CMD_IOACCEL2 129 
 scalar_t__ IOACCEL2_INBOUND_POSTQ_32 ; 
#define  IOACCEL2_TMF 128 
 scalar_t__ SA5_REQUEST_PORT_OFFSET ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dial_down_lockup_detection_during_fw_flash (struct ctlr_info*,struct CommandList*) ; 
 size_t raw_smp_processor_id () ; 
 int /*<<< orphan*/  set_ioaccel1_performant_mode (struct ctlr_info*,struct CommandList*,int) ; 
 int /*<<< orphan*/  set_ioaccel2_performant_mode (struct ctlr_info*,struct CommandList*,int) ; 
 int /*<<< orphan*/  set_ioaccel2_tmf_performant_mode (struct ctlr_info*,struct CommandList*,int) ; 
 int /*<<< orphan*/  set_performant_mode (struct ctlr_info*,struct CommandList*,int) ; 
 int /*<<< orphan*/  stub1 (struct ctlr_info*,struct CommandList*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void __enqueue_cmd_and_start_io(struct ctlr_info *h,
	struct CommandList *c, int reply_queue)
{
	dial_down_lockup_detection_during_fw_flash(h, c);
	atomic_inc(&h->commands_outstanding);
	if (c->device)
		atomic_inc(&c->device->commands_outstanding);

	reply_queue = h->reply_map[raw_smp_processor_id()];
	switch (c->cmd_type) {
	case CMD_IOACCEL1:
		set_ioaccel1_performant_mode(h, c, reply_queue);
		writel(c->busaddr, h->vaddr + SA5_REQUEST_PORT_OFFSET);
		break;
	case CMD_IOACCEL2:
		set_ioaccel2_performant_mode(h, c, reply_queue);
		writel(c->busaddr, h->vaddr + IOACCEL2_INBOUND_POSTQ_32);
		break;
	case IOACCEL2_TMF:
		set_ioaccel2_tmf_performant_mode(h, c, reply_queue);
		writel(c->busaddr, h->vaddr + IOACCEL2_INBOUND_POSTQ_32);
		break;
	default:
		set_performant_mode(h, c, reply_queue);
		h->access.submit_command(h, c);
	}
}