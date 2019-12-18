#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * bus; } ;
struct usb_gadget_driver {TYPE_1__ driver; } ;
struct usb_gadget {int dummy; } ;
struct m66592 {int old_vbus; int /*<<< orphan*/  timer; int /*<<< orphan*/  scount; struct usb_gadget_driver* driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  M66592_INTENB0 ; 
 int /*<<< orphan*/  M66592_INTSTS0 ; 
 int /*<<< orphan*/  M66592_MAX_SAMPLING ; 
 int M66592_URST ; 
 int M66592_VBSE ; 
 int M66592_VBSTS ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  m66592_bset (struct m66592*,int,int /*<<< orphan*/ ) ; 
 int m66592_read (struct m66592*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m66592_start_xclock (struct m66592*) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 struct m66592* to_m66592 (struct usb_gadget*) ; 

__attribute__((used)) static int m66592_udc_start(struct usb_gadget *g,
		struct usb_gadget_driver *driver)
{
	struct m66592 *m66592 = to_m66592(g);

	/* hook up the driver */
	driver->driver.bus = NULL;
	m66592->driver = driver;

	m66592_bset(m66592, M66592_VBSE | M66592_URST, M66592_INTENB0);
	if (m66592_read(m66592, M66592_INTSTS0) & M66592_VBSTS) {
		m66592_start_xclock(m66592);
		/* start vbus sampling */
		m66592->old_vbus = m66592_read(m66592,
					 M66592_INTSTS0) & M66592_VBSTS;
		m66592->scount = M66592_MAX_SAMPLING;
		mod_timer(&m66592->timer, jiffies + msecs_to_jiffies(50));
	}

	return 0;
}