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
struct renesas_usb3 {int dummy; } ;

/* Variables and functions */
 int P0_INT_BFRDY ; 
 int P0_INT_SETUP ; 
 int P0_INT_STSED ; 
 int /*<<< orphan*/  USB3_P0_INT_ENA ; 
 int /*<<< orphan*/  USB3_P0_INT_STA ; 
 int /*<<< orphan*/  usb3_irq_epc_pipe0_bfrdy (struct renesas_usb3*) ; 
 int /*<<< orphan*/  usb3_irq_epc_pipe0_setup (struct renesas_usb3*) ; 
 int /*<<< orphan*/  usb3_irq_epc_pipe0_status_end (struct renesas_usb3*) ; 
 int usb3_read (struct renesas_usb3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb3_write (struct renesas_usb3*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usb3_irq_epc_pipe0(struct renesas_usb3 *usb3)
{
	u32 p0_int_sta = usb3_read(usb3, USB3_P0_INT_STA);

	p0_int_sta &= usb3_read(usb3, USB3_P0_INT_ENA);
	usb3_write(usb3, p0_int_sta, USB3_P0_INT_STA);
	if (p0_int_sta & P0_INT_STSED)
		usb3_irq_epc_pipe0_status_end(usb3);
	if (p0_int_sta & P0_INT_SETUP)
		usb3_irq_epc_pipe0_setup(usb3);
	if (p0_int_sta & P0_INT_BFRDY)
		usb3_irq_epc_pipe0_bfrdy(usb3);
}