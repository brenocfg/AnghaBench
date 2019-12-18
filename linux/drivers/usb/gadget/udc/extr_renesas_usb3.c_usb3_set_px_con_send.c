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
typedef  int u32 ;
struct renesas_usb3_ep {scalar_t__ num; } ;
struct renesas_usb3 {int dummy; } ;

/* Variables and functions */
 int PN_CON_LAST ; 
 int PX_CON_BYTE_EN_BYTES (int) ; 
 int PX_CON_SEND ; 
 int USB3_P0_CON ; 
 int USB3_PN_CON ; 
 struct renesas_usb3* usb3_ep_to_usb3 (struct renesas_usb3_ep*) ; 
 int usb3_read (struct renesas_usb3*,int) ; 
 int /*<<< orphan*/  usb3_write (struct renesas_usb3*,int,int) ; 

__attribute__((used)) static void usb3_set_px_con_send(struct renesas_usb3_ep *usb3_ep, int bytes,
				 bool last)
{
	struct renesas_usb3 *usb3 = usb3_ep_to_usb3(usb3_ep);
	u32 con_reg = usb3_ep->num ? USB3_PN_CON : USB3_P0_CON;
	u32 val = usb3_read(usb3, con_reg);

	val |= PX_CON_SEND | PX_CON_BYTE_EN_BYTES(bytes);
	val |= (usb3_ep->num && last) ? PN_CON_LAST : 0;
	usb3_write(usb3, val, con_reg);
}