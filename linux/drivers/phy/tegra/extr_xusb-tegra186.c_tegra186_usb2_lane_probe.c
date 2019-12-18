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
struct tegra_xusb_lane {unsigned int index; struct device_node* np; struct tegra_xusb_pad* pad; int /*<<< orphan*/ * soc; int /*<<< orphan*/  list; } ;
struct tegra_xusb_usb2_lane {struct tegra_xusb_lane base; } ;
struct tegra_xusb_pad {TYPE_1__* soc; } ;
struct device_node {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * lanes; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct tegra_xusb_lane* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct tegra_xusb_usb2_lane*) ; 
 struct tegra_xusb_usb2_lane* kzalloc (int,int /*<<< orphan*/ ) ; 
 int tegra_xusb_lane_parse_dt (struct tegra_xusb_lane*,struct device_node*) ; 

__attribute__((used)) static struct tegra_xusb_lane *
tegra186_usb2_lane_probe(struct tegra_xusb_pad *pad, struct device_node *np,
			 unsigned int index)
{
	struct tegra_xusb_usb2_lane *usb2;
	int err;

	usb2 = kzalloc(sizeof(*usb2), GFP_KERNEL);
	if (!usb2)
		return ERR_PTR(-ENOMEM);

	INIT_LIST_HEAD(&usb2->base.list);
	usb2->base.soc = &pad->soc->lanes[index];
	usb2->base.index = index;
	usb2->base.pad = pad;
	usb2->base.np = np;

	err = tegra_xusb_lane_parse_dt(&usb2->base, np);
	if (err < 0) {
		kfree(usb2);
		return ERR_PTR(err);
	}

	return &usb2->base;
}