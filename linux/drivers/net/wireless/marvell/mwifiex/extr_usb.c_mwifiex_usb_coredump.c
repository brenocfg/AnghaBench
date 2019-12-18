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
struct usb_interface {int dummy; } ;
struct usb_card_rec {int /*<<< orphan*/  adapter; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MWIFIEX_BSS_ROLE_ANY ; 
 int /*<<< orphan*/  mwifiex_fw_dump_event (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwifiex_get_priv (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct usb_interface* to_usb_interface (struct device*) ; 
 struct usb_card_rec* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static void mwifiex_usb_coredump(struct device *dev)
{
	struct usb_interface *intf = to_usb_interface(dev);
	struct usb_card_rec *card = usb_get_intfdata(intf);

	mwifiex_fw_dump_event(mwifiex_get_priv(card->adapter,
					       MWIFIEX_BSS_ROLE_ANY));
}