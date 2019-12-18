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
typedef  int /*<<< orphan*/  u32 ;
struct renesas_usb3_ep {scalar_t__ num; } ;
struct renesas_usb3 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB3_P0_LNG ; 
 int /*<<< orphan*/  USB3_PN_LNG ; 
 struct renesas_usb3* usb3_ep_to_usb3 (struct renesas_usb3_ep*) ; 
 int /*<<< orphan*/  usb3_read (struct renesas_usb3*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 usb3_get_received_length(struct renesas_usb3_ep *usb3_ep)
{
	struct renesas_usb3 *usb3 = usb3_ep_to_usb3(usb3_ep);
	u32 lng_reg = usb3_ep->num ? USB3_PN_LNG : USB3_P0_LNG;

	return usb3_read(usb3, lng_reg);
}