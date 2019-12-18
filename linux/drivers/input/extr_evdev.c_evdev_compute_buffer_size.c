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
struct input_dev {int hint_events_per_packet; } ;

/* Variables and functions */
 int EVDEV_BUF_PACKETS ; 
 int /*<<< orphan*/  EVDEV_MIN_BUFFER_SIZE ; 
 unsigned int max (int,int /*<<< orphan*/ ) ; 
 unsigned int roundup_pow_of_two (unsigned int) ; 

__attribute__((used)) static unsigned int evdev_compute_buffer_size(struct input_dev *dev)
{
	unsigned int n_events =
		max(dev->hint_events_per_packet * EVDEV_BUF_PACKETS,
		    EVDEV_MIN_BUFFER_SIZE);

	return roundup_pow_of_two(n_events);
}