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
struct stk1160 {int alt; int num_alt; unsigned int* alt_max_pkt_size; int max_pkt_size; int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 unsigned int STK1160_MIN_PKT_SIZE ; 
 int /*<<< orphan*/  stk1160_dbg (char*,unsigned int,...) ; 
 int /*<<< orphan*/  usb_set_interface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static bool stk1160_set_alternate(struct stk1160 *dev)
{
	int i, prev_alt = dev->alt;
	unsigned int min_pkt_size;
	bool new_pkt_size;

	/*
	 * If we don't set right alternate,
	 * then we will get a green screen with junk.
	 */
	min_pkt_size = STK1160_MIN_PKT_SIZE;

	for (i = 0; i < dev->num_alt; i++) {
		/* stop when the selected alt setting offers enough bandwidth */
		if (dev->alt_max_pkt_size[i] >= min_pkt_size) {
			dev->alt = i;
			break;
		/*
		 * otherwise make sure that we end up with the maximum bandwidth
		 * because the min_pkt_size equation might be wrong...
		 */
		} else if (dev->alt_max_pkt_size[i] >
			   dev->alt_max_pkt_size[dev->alt])
			dev->alt = i;
	}

	stk1160_dbg("setting alternate %d\n", dev->alt);

	if (dev->alt != prev_alt) {
		stk1160_dbg("minimum isoc packet size: %u (alt=%d)\n",
				min_pkt_size, dev->alt);
		stk1160_dbg("setting alt %d with wMaxPacketSize=%u\n",
			       dev->alt, dev->alt_max_pkt_size[dev->alt]);
		usb_set_interface(dev->udev, 0, dev->alt);
	}

	new_pkt_size = dev->max_pkt_size != dev->alt_max_pkt_size[dev->alt];
	dev->max_pkt_size = dev->alt_max_pkt_size[dev->alt];

	return new_pkt_size;
}