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
struct udc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  activate_control_endpoints (struct udc*) ; 
 int /*<<< orphan*/  udc_enable_dev_setup_interrupts (struct udc*) ; 
 int /*<<< orphan*/  udc_enable_ep0_interrupts (struct udc*) ; 

__attribute__((used)) static int setup_ep0(struct udc *dev)
{
	activate_control_endpoints(dev);
	/* enable ep0 interrupts */
	udc_enable_ep0_interrupts(dev);
	/* enable device setup interrupts */
	udc_enable_dev_setup_interrupts(dev);

	return 0;
}