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
struct gb_interface {int type; int /*<<< orphan*/  ddbl1_product_id; int /*<<< orphan*/  ddbl1_manufacturer_id; int /*<<< orphan*/  dev; int /*<<< orphan*/  product_id; int /*<<< orphan*/  vendor_id; } ;

/* Variables and functions */
#define  GB_INTERFACE_TYPE_GREYBUS 129 
#define  GB_INTERFACE_TYPE_UNIPRO 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,...) ; 
 int device_add (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gb_interface_type_string (struct gb_interface*) ; 
 int /*<<< orphan*/  trace_gb_interface_add (struct gb_interface*) ; 

int gb_interface_add(struct gb_interface *intf)
{
	int ret;

	ret = device_add(&intf->dev);
	if (ret) {
		dev_err(&intf->dev, "failed to register interface: %d\n", ret);
		return ret;
	}

	trace_gb_interface_add(intf);

	dev_info(&intf->dev, "Interface added (%s)\n",
		 gb_interface_type_string(intf));

	switch (intf->type) {
	case GB_INTERFACE_TYPE_GREYBUS:
		dev_info(&intf->dev, "GMP VID=0x%08x, PID=0x%08x\n",
			 intf->vendor_id, intf->product_id);
		/* fall-through */
	case GB_INTERFACE_TYPE_UNIPRO:
		dev_info(&intf->dev, "DDBL1 Manufacturer=0x%08x, Product=0x%08x\n",
			 intf->ddbl1_manufacturer_id,
			 intf->ddbl1_product_id);
		break;
	default:
		break;
	}

	return 0;
}