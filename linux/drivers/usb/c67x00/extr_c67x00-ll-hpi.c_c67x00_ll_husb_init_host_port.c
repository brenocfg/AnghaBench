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
 int HOST_MODE ; 
 int /*<<< orphan*/  HOST_STAT_MASK ; 
 int /*<<< orphan*/  USB_CTL_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c67x00_ll_husb_sie_init (struct c67x00_sie*) ; 
 int /*<<< orphan*/  c67x00_ll_usb_clear_status (struct c67x00_sie*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int hpi_read_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpi_set_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sie_dev (struct c67x00_sie*) ; 

void c67x00_ll_husb_init_host_port(struct c67x00_sie *sie)
{
	/* Set port into host mode */
	hpi_set_bits(sie->dev, USB_CTL_REG(sie->sie_num), HOST_MODE);
	c67x00_ll_husb_sie_init(sie);
	/* Clear interrupts */
	c67x00_ll_usb_clear_status(sie, HOST_STAT_MASK);
	/* Check */
	if (!(hpi_read_word(sie->dev, USB_CTL_REG(sie->sie_num)) & HOST_MODE))
		dev_warn(sie_dev(sie),
			 "SIE %d not set to host mode\n", sie->sie_num);
}