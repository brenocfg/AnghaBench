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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int size; } ;
struct hfi_msg_sys_property_info_pkt {int num_properties; int /*<<< orphan*/ * data; TYPE_1__ hdr; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
sys_get_prop_image_version(struct device *dev,
			   struct hfi_msg_sys_property_info_pkt *pkt)
{
	int req_bytes;

	req_bytes = pkt->hdr.size - sizeof(*pkt);

	if (req_bytes < 128 || !pkt->data[1] || pkt->num_properties > 1)
		/* bad packet */
		return;

	dev_dbg(dev, "F/W version: %s\n", (u8 *)&pkt->data[1]);
}