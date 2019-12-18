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
struct udc {int connected; int /*<<< orphan*/  dev; scalar_t__ driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  udc_basic_init (struct udc*) ; 
 int /*<<< orphan*/  udc_enable_dev_setup_interrupts (struct udc*) ; 

__attribute__((used)) static void start_udc(struct udc *udc)
{
	if (udc->driver) {
		dev_info(udc->dev, "Connecting...\n");
		udc_enable_dev_setup_interrupts(udc);
		udc_basic_init(udc);
		udc->connected = 1;
	}
}