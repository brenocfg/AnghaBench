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
struct venus_inst {TYPE_1__* ops; int /*<<< orphan*/  error; } ;
struct venus_core {int dummy; } ;
struct hfi_msg_session_empty_buffer_done_pkt {int /*<<< orphan*/  offset; int /*<<< orphan*/  filled_len; int /*<<< orphan*/  input_tag; int /*<<< orphan*/  error_type; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* buf_done ) (struct venus_inst*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  HFI_BUFFER_INPUT ; 
 int /*<<< orphan*/  stub1 (struct venus_inst*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hfi_session_etb_done(struct venus_core *core,
				 struct venus_inst *inst, void *packet)
{
	struct hfi_msg_session_empty_buffer_done_pkt *pkt = packet;

	inst->error = pkt->error_type;
	inst->ops->buf_done(inst, HFI_BUFFER_INPUT, pkt->input_tag,
			    pkt->filled_len, pkt->offset, 0, 0, 0);
}