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

/* Variables and functions */
 int EVENT_WORDS_PER_PAGE ; 
 int event_array_pages ; 

__attribute__((used)) static unsigned evtchn_fifo_nr_channels(void)
{
	return event_array_pages * EVENT_WORDS_PER_PAGE;
}