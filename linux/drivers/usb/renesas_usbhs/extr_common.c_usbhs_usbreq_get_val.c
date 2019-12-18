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
typedef  int u16 ;
struct usbhs_priv {int dummy; } ;
struct usb_ctrlrequest {int bRequest; int bRequestType; void* wLength; void* wIndex; void* wValue; } ;

/* Variables and functions */
 int /*<<< orphan*/  USBINDX ; 
 int /*<<< orphan*/  USBLENG ; 
 int /*<<< orphan*/  USBREQ ; 
 int /*<<< orphan*/  USBVAL ; 
 void* cpu_to_le16 (int) ; 
 int usbhs_read (struct usbhs_priv*,int /*<<< orphan*/ ) ; 

void usbhs_usbreq_get_val(struct usbhs_priv *priv, struct usb_ctrlrequest *req)
{
	u16 val;

	val = usbhs_read(priv, USBREQ);
	req->bRequest		= (val >> 8) & 0xFF;
	req->bRequestType	= (val >> 0) & 0xFF;

	req->wValue	= cpu_to_le16(usbhs_read(priv, USBVAL));
	req->wIndex	= cpu_to_le16(usbhs_read(priv, USBINDX));
	req->wLength	= cpu_to_le16(usbhs_read(priv, USBLENG));
}