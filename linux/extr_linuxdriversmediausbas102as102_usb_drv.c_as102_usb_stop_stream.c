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
struct as102_dev_t {int /*<<< orphan*/ * stream_urb; } ;

/* Variables and functions */
 int MAX_STREAM_URB ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void as102_usb_stop_stream(struct as102_dev_t *dev)
{
	int i;

	for (i = 0; i < MAX_STREAM_URB; i++)
		usb_kill_urb(dev->stream_urb[i]);
}