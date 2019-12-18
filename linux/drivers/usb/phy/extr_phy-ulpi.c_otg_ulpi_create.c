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
struct usb_phy_io_ops {int dummy; } ;
struct usb_phy {char* label; unsigned int flags; int /*<<< orphan*/  init; struct usb_otg* otg; struct usb_phy_io_ops* io_ops; } ;
struct usb_otg {int /*<<< orphan*/  set_vbus; int /*<<< orphan*/  set_host; struct usb_phy* usb_phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct usb_phy*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ulpi_init ; 
 int /*<<< orphan*/  ulpi_set_host ; 
 int /*<<< orphan*/  ulpi_set_vbus ; 

struct usb_phy *
otg_ulpi_create(struct usb_phy_io_ops *ops,
		unsigned int flags)
{
	struct usb_phy *phy;
	struct usb_otg *otg;

	phy = kzalloc(sizeof(*phy), GFP_KERNEL);
	if (!phy)
		return NULL;

	otg = kzalloc(sizeof(*otg), GFP_KERNEL);
	if (!otg) {
		kfree(phy);
		return NULL;
	}

	phy->label	= "ULPI";
	phy->flags	= flags;
	phy->io_ops	= ops;
	phy->otg	= otg;
	phy->init	= ulpi_init;

	otg->usb_phy	= phy;
	otg->set_host	= ulpi_set_host;
	otg->set_vbus	= ulpi_set_vbus;

	return phy;
}