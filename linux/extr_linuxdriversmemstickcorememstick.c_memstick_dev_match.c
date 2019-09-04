#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct memstick_device_id {int match_flags; scalar_t__ type; scalar_t__ category; scalar_t__ class; } ;
struct TYPE_2__ {scalar_t__ type; scalar_t__ category; scalar_t__ class; } ;
struct memstick_dev {TYPE_1__ id; } ;

/* Variables and functions */
 int MEMSTICK_MATCH_ALL ; 

__attribute__((used)) static int memstick_dev_match(struct memstick_dev *card,
			      struct memstick_device_id *id)
{
	if (id->match_flags & MEMSTICK_MATCH_ALL) {
		if ((id->type == card->id.type)
		    && (id->category == card->id.category)
		    && (id->class == card->id.class))
			return 1;
	}

	return 0;
}