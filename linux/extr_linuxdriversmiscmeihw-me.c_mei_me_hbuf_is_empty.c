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
struct mei_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ mei_hbuf_filled_slots (struct mei_device*) ; 

__attribute__((used)) static bool mei_me_hbuf_is_empty(struct mei_device *dev)
{
	return mei_hbuf_filled_slots(dev) == 0;
}