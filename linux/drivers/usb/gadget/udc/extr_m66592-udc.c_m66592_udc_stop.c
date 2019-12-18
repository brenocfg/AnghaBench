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
struct usb_gadget {int dummy; } ;
struct m66592 {int /*<<< orphan*/ * driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  M66592_INTENB0 ; 
 int M66592_URST ; 
 int M66592_VBSE ; 
 int /*<<< orphan*/  disable_controller (struct m66592*) ; 
 int /*<<< orphan*/  init_controller (struct m66592*) ; 
 int /*<<< orphan*/  m66592_bclr (struct m66592*,int,int /*<<< orphan*/ ) ; 
 struct m66592* to_m66592 (struct usb_gadget*) ; 

__attribute__((used)) static int m66592_udc_stop(struct usb_gadget *g)
{
	struct m66592 *m66592 = to_m66592(g);

	m66592_bclr(m66592, M66592_VBSE | M66592_URST, M66592_INTENB0);

	init_controller(m66592);
	disable_controller(m66592);

	m66592->driver = NULL;

	return 0;
}