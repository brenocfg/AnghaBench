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
struct venus_core {int /*<<< orphan*/  dev; } ;
struct hfi_msg_sys_pc_prep_done_pkt {int /*<<< orphan*/  error_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hfi_sys_pc_prepare_done(struct venus_core *core,
				    struct venus_inst *inst, void *packet)
{
	struct hfi_msg_sys_pc_prep_done_pkt *pkt = packet;

	dev_dbg(core->dev, "pc prepare done (error %x)\n", pkt->error_type);
}