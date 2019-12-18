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
typedef  int /*<<< orphan*/  u32 ;
struct venus_inst {int dummy; } ;
struct venus_core {struct device* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  session_id; } ;
struct hfi_session_pkt {TYPE_1__ shdr; } ;
struct hfi_pkt_hdr {scalar_t__ size; int /*<<< orphan*/  pkt_type; } ;
struct hfi_done_handler {scalar_t__ pkt_sz; scalar_t__ pkt_sz2; int /*<<< orphan*/  (* done ) (struct venus_core*,struct venus_inst*,struct hfi_pkt_hdr*) ;int /*<<< orphan*/  pkt; scalar_t__ is_sys_pkt; } ;
struct device {int dummy; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct hfi_done_handler*) ; 
 int /*<<< orphan*/  HFI_MSG_EVENT_NOTIFY ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hfi_done_handler* handlers ; 
 int /*<<< orphan*/  stub1 (struct venus_core*,struct venus_inst*,struct hfi_pkt_hdr*) ; 
 struct venus_inst* to_instance (struct venus_core*,int /*<<< orphan*/ ) ; 

u32 hfi_process_msg_packet(struct venus_core *core, struct hfi_pkt_hdr *hdr)
{
	const struct hfi_done_handler *handler;
	struct device *dev = core->dev;
	struct venus_inst *inst;
	bool found = false;
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(handlers); i++) {
		handler = &handlers[i];
		if (handler->pkt != hdr->pkt_type)
			continue;
		found = true;
		break;
	}

	if (!found)
		return hdr->pkt_type;

	if (hdr->size && hdr->size < handler->pkt_sz &&
	    hdr->size < handler->pkt_sz2) {
		dev_err(dev, "bad packet size (%d should be %d, pkt type:%x)\n",
			hdr->size, handler->pkt_sz, hdr->pkt_type);

		return hdr->pkt_type;
	}

	if (handler->is_sys_pkt) {
		inst = NULL;
	} else {
		struct hfi_session_pkt *pkt;

		pkt = (struct hfi_session_pkt *)hdr;
		inst = to_instance(core, pkt->shdr.session_id);

		if (!inst)
			dev_warn(dev, "no valid instance(pkt session_id:%x, pkt:%x)\n",
				 pkt->shdr.session_id,
				 handler ? handler->pkt : 0);

		/*
		 * Event of type HFI_EVENT_SYS_ERROR will not have any session
		 * associated with it
		 */
		if (!inst && hdr->pkt_type != HFI_MSG_EVENT_NOTIFY) {
			dev_err(dev, "got invalid session id:%x\n",
				pkt->shdr.session_id);
			goto invalid_session;
		}
	}

	handler->done(core, inst, hdr);

invalid_session:
	return hdr->pkt_type;
}