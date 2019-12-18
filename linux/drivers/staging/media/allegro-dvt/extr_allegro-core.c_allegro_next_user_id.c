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
struct allegro_dev {unsigned long channel_user_ids; } ;

/* Variables and functions */
 unsigned long EBUSY ; 
 unsigned long ffz (unsigned long) ; 

__attribute__((used)) static unsigned long allegro_next_user_id(struct allegro_dev *dev)
{
	if (dev->channel_user_ids == ~0UL)
		return -EBUSY;

	return ffz(dev->channel_user_ids);
}