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
struct hfi_sys_set_property_pkt {int num_properties; int /*<<< orphan*/ * data; TYPE_1__ hdr; } ;
struct hfi_enable {int /*<<< orphan*/  enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  HFI_CMD_SYS_SET_PROPERTY ; 
 int /*<<< orphan*/  HFI_PROPERTY_SYS_CODEC_POWER_PLANE_CTRL ; 

void pkt_sys_power_control(struct hfi_sys_set_property_pkt *pkt, u32 enable)
{
	struct hfi_enable *hfi = (struct hfi_enable *)&pkt->data[1];

	pkt->hdr.size = sizeof(*pkt) + sizeof(*hfi) + sizeof(u32);
	pkt->hdr.pkt_type = HFI_CMD_SYS_SET_PROPERTY;
	pkt->num_properties = 1;
	pkt->data[0] = HFI_PROPERTY_SYS_CODEC_POWER_PLANE_CTRL;
	hfi->enable = enable;
}