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
struct TYPE_2__ {int size; int /*<<< orphan*/  pkt_type; } ;
struct hfi_sys_pc_prep_pkt {TYPE_1__ hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  HFI_CMD_SYS_PC_PREP ; 

void pkt_sys_pc_prep(struct hfi_sys_pc_prep_pkt *pkt)
{
	pkt->hdr.size = sizeof(*pkt);
	pkt->hdr.pkt_type = HFI_CMD_SYS_PC_PREP;
}