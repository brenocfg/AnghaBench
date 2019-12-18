#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * parent; } ;
struct hid_device {int vendor; int product; int /*<<< orphan*/  name; TYPE_2__ dev; int /*<<< orphan*/ * ll_driver; struct gb_hid* driver_data; int /*<<< orphan*/  country; void* version; } ;
struct TYPE_5__ {int /*<<< orphan*/  bCountryCode; int /*<<< orphan*/  wProductID; int /*<<< orphan*/  wVendorID; int /*<<< orphan*/  bcdHID; } ;
struct gb_hid {TYPE_4__* connection; TYPE_1__ hdesc; struct hid_device* hid; } ;
struct TYPE_8__ {TYPE_3__* bundle; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 char* dev_name (int /*<<< orphan*/ *) ; 
 int gb_hid_get_desc (struct gb_hid*) ; 
 int /*<<< orphan*/  gb_hid_ll_driver ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,int,int) ; 

__attribute__((used)) static int gb_hid_init(struct gb_hid *ghid)
{
	struct hid_device *hid = ghid->hid;
	int ret;

	ret = gb_hid_get_desc(ghid);
	if (ret)
		return ret;

	hid->version = le16_to_cpu(ghid->hdesc.bcdHID);
	hid->vendor = le16_to_cpu(ghid->hdesc.wVendorID);
	hid->product = le16_to_cpu(ghid->hdesc.wProductID);
	hid->country = ghid->hdesc.bCountryCode;

	hid->driver_data = ghid;
	hid->ll_driver = &gb_hid_ll_driver;
	hid->dev.parent = &ghid->connection->bundle->dev;
//	hid->bus = BUS_GREYBUS; /* Need a bustype for GREYBUS in <linux/input.h> */

	/* Set HID device's name */
	snprintf(hid->name, sizeof(hid->name), "%s %04X:%04X",
		 dev_name(&ghid->connection->bundle->dev),
		 hid->vendor, hid->product);

	return 0;
}