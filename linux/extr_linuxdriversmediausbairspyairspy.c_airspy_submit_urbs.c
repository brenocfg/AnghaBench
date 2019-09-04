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
struct airspy {int urbs_initialized; int /*<<< orphan*/  urbs_submitted; int /*<<< orphan*/  dev; int /*<<< orphan*/ * urb_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  airspy_kill_urbs (struct airspy*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int airspy_submit_urbs(struct airspy *s)
{
	int i, ret;

	for (i = 0; i < s->urbs_initialized; i++) {
		dev_dbg(s->dev, "submit urb=%d\n", i);
		ret = usb_submit_urb(s->urb_list[i], GFP_ATOMIC);
		if (ret) {
			dev_err(s->dev, "Could not submit URB no. %d - get them all back\n",
					i);
			airspy_kill_urbs(s);
			return ret;
		}
		s->urbs_submitted++;
	}

	return 0;
}