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
struct usbhs_priv {int dummy; } ;
struct usb_ctrlrequest {int bRequest; int bRequestType; int /*<<< orphan*/  wLength; int /*<<< orphan*/  wIndex; int /*<<< orphan*/  wValue; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCPCTR ; 
 int /*<<< orphan*/  SUREQ ; 
 int /*<<< orphan*/  USBINDX ; 
 int /*<<< orphan*/  USBLENG ; 
 int /*<<< orphan*/  USBREQ ; 
 int /*<<< orphan*/  USBVAL ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbhs_bset (struct usbhs_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbhs_write (struct usbhs_priv*,int /*<<< orphan*/ ,int) ; 

void usbhs_usbreq_set_val(struct usbhs_priv *priv, struct usb_ctrlrequest *req)
{
	usbhs_write(priv, USBREQ,  (req->bRequest << 8) | req->bRequestType);
	usbhs_write(priv, USBVAL,  le16_to_cpu(req->wValue));
	usbhs_write(priv, USBINDX, le16_to_cpu(req->wIndex));
	usbhs_write(priv, USBLENG, le16_to_cpu(req->wLength));

	usbhs_bset(priv, DCPCTR, SUREQ, SUREQ);
}