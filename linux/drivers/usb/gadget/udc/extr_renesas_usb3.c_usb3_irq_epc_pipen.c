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
struct renesas_usb3 {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int PN_INT_BFRDY ; 
 int PN_INT_LSTTR ; 
 int /*<<< orphan*/  USB3_PN_INT_ENA ; 
 int /*<<< orphan*/  USB3_PN_INT_STA ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb3_irq_epc_pipen_bfrdy (struct renesas_usb3*,int) ; 
 int /*<<< orphan*/  usb3_irq_epc_pipen_lsttr (struct renesas_usb3*,int) ; 
 scalar_t__ usb3_pn_change (struct renesas_usb3*,int) ; 
 int usb3_read (struct renesas_usb3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb3_write (struct renesas_usb3*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usb3_irq_epc_pipen(struct renesas_usb3 *usb3, int num)
{
	u32 pn_int_sta;

	spin_lock(&usb3->lock);
	if (usb3_pn_change(usb3, num) < 0) {
		spin_unlock(&usb3->lock);
		return;
	}

	pn_int_sta = usb3_read(usb3, USB3_PN_INT_STA);
	pn_int_sta &= usb3_read(usb3, USB3_PN_INT_ENA);
	usb3_write(usb3, pn_int_sta, USB3_PN_INT_STA);
	spin_unlock(&usb3->lock);
	if (pn_int_sta & PN_INT_LSTTR)
		usb3_irq_epc_pipen_lsttr(usb3, num);
	if (pn_int_sta & PN_INT_BFRDY)
		usb3_irq_epc_pipen_bfrdy(usb3, num);
}