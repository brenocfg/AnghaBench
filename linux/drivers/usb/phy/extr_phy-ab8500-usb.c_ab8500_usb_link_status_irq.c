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
struct ab8500_usb {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  abx500_usb_link_status_update (struct ab8500_usb*) ; 

__attribute__((used)) static irqreturn_t ab8500_usb_link_status_irq(int irq, void *data)
{
	struct ab8500_usb *ab = (struct ab8500_usb *)data;

	abx500_usb_link_status_update(ab);

	return IRQ_HANDLED;
}