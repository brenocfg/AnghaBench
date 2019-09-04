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
struct mei_me_hw {unsigned char hbuf_depth; } ;
struct mei_device {int dummy; } ;

/* Variables and functions */
 int EOVERFLOW ; 
 unsigned char mei_hbuf_filled_slots (struct mei_device*) ; 
 struct mei_me_hw* to_me_hw (struct mei_device*) ; 

__attribute__((used)) static int mei_me_hbuf_empty_slots(struct mei_device *dev)
{
	struct mei_me_hw *hw = to_me_hw(dev);
	unsigned char filled_slots, empty_slots;

	filled_slots = mei_hbuf_filled_slots(dev);
	empty_slots = hw->hbuf_depth - filled_slots;

	/* check for overflow */
	if (filled_slots > hw->hbuf_depth)
		return -EOVERFLOW;

	return empty_slots;
}