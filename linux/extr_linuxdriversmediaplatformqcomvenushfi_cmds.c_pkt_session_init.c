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
typedef  void* u32 ;
struct TYPE_3__ {int size; int /*<<< orphan*/  pkt_type; } ;
struct TYPE_4__ {int /*<<< orphan*/  session_id; TYPE_1__ hdr; } ;
struct hfi_session_init_pkt {void* session_codec; void* session_domain; TYPE_2__ shdr; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HFI_CMD_SYS_SESSION_INIT ; 
 int /*<<< orphan*/  hash32_ptr (void*) ; 

int pkt_session_init(struct hfi_session_init_pkt *pkt, void *cookie,
		     u32 session_type, u32 codec)
{
	if (!pkt || !cookie || !codec)
		return -EINVAL;

	pkt->shdr.hdr.size = sizeof(*pkt);
	pkt->shdr.hdr.pkt_type = HFI_CMD_SYS_SESSION_INIT;
	pkt->shdr.session_id = hash32_ptr(cookie);
	pkt->session_domain = session_type;
	pkt->session_codec = codec;

	return 0;
}