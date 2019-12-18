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
struct renesas_usb3 {int dummy; } ;

/* Variables and functions */
 int AXI_INT_DMAINT ; 
 int AXI_INT_EPCINT ; 
 int /*<<< orphan*/  USB3_AXI_INT_ENA ; 
 int /*<<< orphan*/  USB3_DMA_INT_ENA ; 
 int /*<<< orphan*/  USB3_DMA_INT_STA ; 
 int /*<<< orphan*/  usb3_set_bit (struct renesas_usb3*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb3_write (struct renesas_usb3*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usb3_init_axi_bridge(struct renesas_usb3 *usb3)
{
	/* Set AXI_INT */
	usb3_write(usb3, ~0, USB3_DMA_INT_STA);
	usb3_write(usb3, 0, USB3_DMA_INT_ENA);
	usb3_set_bit(usb3, AXI_INT_DMAINT | AXI_INT_EPCINT, USB3_AXI_INT_ENA);
}