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
typedef  int u64 ;
typedef  int u32 ;
struct gb_interface {scalar_t__ ddbl1_manufacturer_id; int vendor_id; int product_id; int serial_number; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DME_TOSHIBA_GMP_PID ; 
 int /*<<< orphan*/  DME_TOSHIBA_GMP_SN0 ; 
 int /*<<< orphan*/  DME_TOSHIBA_GMP_SN1 ; 
 int /*<<< orphan*/  DME_TOSHIBA_GMP_VID ; 
 int ENODEV ; 
 scalar_t__ TOSHIBA_DMID ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int gb_interface_dme_attr_get (struct gb_interface*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int gb_interface_read_ara_dme(struct gb_interface *intf)
{
	u32 sn0, sn1;
	int ret;

	/*
	 * Unless this is a Toshiba bridge, bail out until we have defined
	 * standard GMP attributes.
	 */
	if (intf->ddbl1_manufacturer_id != TOSHIBA_DMID) {
		dev_err(&intf->dev, "unknown manufacturer %08x\n",
			intf->ddbl1_manufacturer_id);
		return -ENODEV;
	}

	ret = gb_interface_dme_attr_get(intf, DME_TOSHIBA_GMP_VID,
					&intf->vendor_id);
	if (ret)
		return ret;

	ret = gb_interface_dme_attr_get(intf, DME_TOSHIBA_GMP_PID,
					&intf->product_id);
	if (ret)
		return ret;

	ret = gb_interface_dme_attr_get(intf, DME_TOSHIBA_GMP_SN0, &sn0);
	if (ret)
		return ret;

	ret = gb_interface_dme_attr_get(intf, DME_TOSHIBA_GMP_SN1, &sn1);
	if (ret)
		return ret;

	intf->serial_number = (u64)sn1 << 32 | sn0;

	return 0;
}