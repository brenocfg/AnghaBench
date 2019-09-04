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
struct airspy {int urbs_initialized; scalar_t__* urb_list; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  airspy_kill_urbs (struct airspy*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  usb_free_urb (scalar_t__) ; 

__attribute__((used)) static int airspy_free_urbs(struct airspy *s)
{
	int i;

	airspy_kill_urbs(s);

	for (i = s->urbs_initialized - 1; i >= 0; i--) {
		if (s->urb_list[i]) {
			dev_dbg(s->dev, "free urb=%d\n", i);
			/* free the URBs */
			usb_free_urb(s->urb_list[i]);
		}
	}
	s->urbs_initialized = 0;

	return 0;
}