#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct TYPE_4__ {struct device dev; } ;
struct uwb_rc {TYPE_1__ uwb_dev; } ;
struct TYPE_6__ {TYPE_2__* bus; } ;
struct uwb_dev {TYPE_3__ dev; struct uwb_beca_e* bce; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  mac_addr; } ;
struct uwb_beca_e {struct uwb_dev* uwb_dev; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/ * mac_addr; } ;
typedef  int /*<<< orphan*/  macbuf ;
typedef  int /*<<< orphan*/  devbuf ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int UWB_ADDR_STRSIZE ; 
 int /*<<< orphan*/  UWB_NOTIF_ONAIR ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_3__*,char*,char*) ; 
 int /*<<< orphan*/  kfree (struct uwb_dev*) ; 
 struct uwb_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uwb_bce_get (struct uwb_beca_e*) ; 
 int /*<<< orphan*/  uwb_bce_put (struct uwb_beca_e*) ; 
 TYPE_2__ uwb_bus_type ; 
 int uwb_dev_add (struct uwb_dev*,struct device*,struct uwb_rc*) ; 
 int /*<<< orphan*/  uwb_dev_addr_print (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uwb_dev_init (struct uwb_dev*) ; 
 int /*<<< orphan*/  uwb_mac_addr_print (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uwb_notify (struct uwb_rc*,struct uwb_dev*,int /*<<< orphan*/ ) ; 

void uwbd_dev_onair(struct uwb_rc *rc, struct uwb_beca_e *bce)
{
	int result;
	struct device *dev = &rc->uwb_dev.dev;
	struct uwb_dev *uwb_dev;
	char macbuf[UWB_ADDR_STRSIZE], devbuf[UWB_ADDR_STRSIZE];

	uwb_mac_addr_print(macbuf, sizeof(macbuf), bce->mac_addr);
	uwb_dev_addr_print(devbuf, sizeof(devbuf), &bce->dev_addr);
	uwb_dev = kzalloc(sizeof(struct uwb_dev), GFP_KERNEL);
	if (uwb_dev == NULL) {
		dev_err(dev, "new device %s: Cannot allocate memory\n",
			macbuf);
		return;
	}
	uwb_dev_init(uwb_dev);		/* This sets refcnt to one, we own it */
	uwb_dev->dev.bus = &uwb_bus_type;
	uwb_dev->mac_addr = *bce->mac_addr;
	uwb_dev->dev_addr = bce->dev_addr;
	dev_set_name(&uwb_dev->dev, "%s", macbuf);

	/* plug the beacon cache */
	bce->uwb_dev = uwb_dev;
	uwb_dev->bce = bce;
	uwb_bce_get(bce);		/* released in uwb_dev_sys_release() */

	result = uwb_dev_add(uwb_dev, &rc->uwb_dev.dev, rc);
	if (result < 0) {
		dev_err(dev, "new device %s: cannot instantiate device\n",
			macbuf);
		goto error_dev_add;
	}

	dev_info(dev, "uwb device (mac %s dev %s) connected to %s %s\n",
		 macbuf, devbuf, uwb_dev->dev.bus->name,
		 dev_name(&(rc->uwb_dev.dev)));
	uwb_notify(rc, uwb_dev, UWB_NOTIF_ONAIR);
	return;

error_dev_add:
	bce->uwb_dev = NULL;
	uwb_bce_put(bce);
	kfree(uwb_dev);
	return;
}