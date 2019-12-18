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
typedef  int u32 ;
struct TYPE_3__ {int size; int /*<<< orphan*/  pkt_type; } ;
struct TYPE_4__ {int /*<<< orphan*/  session_id; TYPE_1__ hdr; } ;
struct hfi_session_flush_pkt {int flush_type; TYPE_2__ shdr; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HFI_CMD_SESSION_FLUSH ; 
#define  HFI_FLUSH_ALL 131 
#define  HFI_FLUSH_INPUT 130 
#define  HFI_FLUSH_OUTPUT 129 
#define  HFI_FLUSH_OUTPUT2 128 
 int /*<<< orphan*/  hash32_ptr (void*) ; 

int pkt_session_flush(struct hfi_session_flush_pkt *pkt, void *cookie, u32 type)
{
	switch (type) {
	case HFI_FLUSH_INPUT:
	case HFI_FLUSH_OUTPUT:
	case HFI_FLUSH_OUTPUT2:
	case HFI_FLUSH_ALL:
		break;
	default:
		return -EINVAL;
	}

	pkt->shdr.hdr.size = sizeof(*pkt);
	pkt->shdr.hdr.pkt_type = HFI_CMD_SESSION_FLUSH;
	pkt->shdr.session_id = hash32_ptr(cookie);
	pkt->flush_type = type;

	return 0;
}