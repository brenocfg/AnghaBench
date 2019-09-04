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
struct TYPE_2__ {int size; int /*<<< orphan*/  pkt_type; } ;
struct hfi_sys_ping_pkt {int /*<<< orphan*/  client_data; TYPE_1__ hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  HFI_CMD_SYS_PING ; 

void pkt_sys_ping(struct hfi_sys_ping_pkt *pkt, u32 cookie)
{
	pkt->hdr.size = sizeof(*pkt);
	pkt->hdr.pkt_type = HFI_CMD_SYS_PING;
	pkt->client_data = cookie;
}