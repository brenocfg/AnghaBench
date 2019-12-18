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
 int as102_submit_urb_stream (struct as102_dev_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  as102_usb_stop_stream (struct as102_dev_t*) ; 

__attribute__((used)) static int as102_usb_start_stream(struct as102_dev_t *dev)
{
	int i, ret = 0;

	for (i = 0; i < MAX_STREAM_URB; i++) {
		ret = as102_submit_urb_stream(dev, dev->stream_urb[i]);
		if (ret) {
			as102_usb_stop_stream(dev);
			return ret;
		}
	}

	return 0;
}