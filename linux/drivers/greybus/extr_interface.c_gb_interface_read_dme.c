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
struct gb_interface {int dme_read; scalar_t__ ddbl1_manufacturer_id; scalar_t__ ddbl1_product_id; int /*<<< orphan*/  quirks; } ;

/* Variables and functions */
 int /*<<< orphan*/  DME_DDBL1_MANUFACTURERID ; 
 int /*<<< orphan*/  DME_DDBL1_PRODUCTID ; 
 int /*<<< orphan*/  GB_INTERFACE_QUIRK_NO_GMP_IDS ; 
 int /*<<< orphan*/  GB_INTERFACE_QUIRK_NO_INIT_STATUS ; 
 scalar_t__ TOSHIBA_DMID ; 
 scalar_t__ TOSHIBA_ES2_BRIDGE_DPID ; 
 int gb_interface_dme_attr_get (struct gb_interface*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int gb_interface_read_ara_dme (struct gb_interface*) ; 

__attribute__((used)) static int gb_interface_read_dme(struct gb_interface *intf)
{
	int ret;

	/* DME attributes have already been read */
	if (intf->dme_read)
		return 0;

	ret = gb_interface_dme_attr_get(intf, DME_DDBL1_MANUFACTURERID,
					&intf->ddbl1_manufacturer_id);
	if (ret)
		return ret;

	ret = gb_interface_dme_attr_get(intf, DME_DDBL1_PRODUCTID,
					&intf->ddbl1_product_id);
	if (ret)
		return ret;

	if (intf->ddbl1_manufacturer_id == TOSHIBA_DMID &&
	    intf->ddbl1_product_id == TOSHIBA_ES2_BRIDGE_DPID) {
		intf->quirks |= GB_INTERFACE_QUIRK_NO_GMP_IDS;
		intf->quirks |= GB_INTERFACE_QUIRK_NO_INIT_STATUS;
	}

	ret = gb_interface_read_ara_dme(intf);
	if (ret)
		return ret;

	intf->dme_read = true;

	return 0;
}