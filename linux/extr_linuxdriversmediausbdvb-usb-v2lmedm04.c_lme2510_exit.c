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
struct dvb_usb_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (void*) ; 
 void* lme2510_exit_int (struct dvb_usb_device*) ; 

__attribute__((used)) static void lme2510_exit(struct dvb_usb_device *d)
{
	void *usb_buffer;

	if (d != NULL) {
		usb_buffer = lme2510_exit_int(d);
		kfree(usb_buffer);
	}
}