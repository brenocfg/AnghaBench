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
struct c67x00_sie {int /*<<< orphan*/  sie_num; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DONE_IRQ_EN ; 
 int /*<<< orphan*/  HOST_IRQ_EN_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPI_IRQ_ROUTING_REG ; 
 int /*<<< orphan*/  PORT_CONNECT_CHANGE (int) ; 
 int PORT_RES_EN (int) ; 
 int SOFEOP_TO_CPU_EN (int /*<<< orphan*/ ) ; 
 int SOF_EOP_IRQ_EN ; 
 int /*<<< orphan*/  USB_CTL_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c67x00_ll_usb_clear_status (struct c67x00_sie*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpi_set_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void c67x00_ll_husb_reset_port(struct c67x00_sie *sie, int port)
{
	/* Clear connect change */
	c67x00_ll_usb_clear_status(sie, PORT_CONNECT_CHANGE(port));

	/* Enable interrupts */
	hpi_set_bits(sie->dev, HPI_IRQ_ROUTING_REG,
		     SOFEOP_TO_CPU_EN(sie->sie_num));
	hpi_set_bits(sie->dev, HOST_IRQ_EN_REG(sie->sie_num),
		     SOF_EOP_IRQ_EN | DONE_IRQ_EN);

	/* Enable pull down transistors */
	hpi_set_bits(sie->dev, USB_CTL_REG(sie->sie_num), PORT_RES_EN(port));
}