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
struct sisusb_usb_data {int /*<<< orphan*/  wait_q; } ;

/* Variables and functions */
 int HZ ; 
 int sisusb_all_free (struct sisusb_usb_data*) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int sisusb_wait_all_out_complete(struct sisusb_usb_data *sisusb)
{
	int timeout = 5 * HZ, i = 1;

	wait_event_timeout(sisusb->wait_q, (i = sisusb_all_free(sisusb)),
			timeout);

	return i;
}