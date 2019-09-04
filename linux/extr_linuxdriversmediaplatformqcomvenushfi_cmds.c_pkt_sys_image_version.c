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
struct hfi_sys_get_property_pkt {int num_properties; int /*<<< orphan*/ * data; TYPE_1__ hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  HFI_CMD_SYS_GET_PROPERTY ; 
 int /*<<< orphan*/  HFI_PROPERTY_SYS_IMAGE_VERSION ; 

void pkt_sys_image_version(struct hfi_sys_get_property_pkt *pkt)
{
	pkt->hdr.size = sizeof(*pkt);
	pkt->hdr.pkt_type = HFI_CMD_SYS_GET_PROPERTY;
	pkt->num_properties = 1;
	pkt->data[0] = HFI_PROPERTY_SYS_IMAGE_VERSION;
}