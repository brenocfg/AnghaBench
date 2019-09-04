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
struct venus_inst {int dummy; } ;
struct venus_core {int /*<<< orphan*/  done; int /*<<< orphan*/  error; } ;
struct hfi_msg_sys_release_resource_done_pkt {int /*<<< orphan*/  error_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hfi_sys_rel_resource_done(struct venus_core *core,
				      struct venus_inst *inst,
				      void *packet)
{
	struct hfi_msg_sys_release_resource_done_pkt *pkt = packet;

	core->error = pkt->error_type;
	complete(&core->done);
}