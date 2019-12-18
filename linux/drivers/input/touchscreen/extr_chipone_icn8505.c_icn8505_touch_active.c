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
typedef  scalar_t__ u8 ;

/* Variables and functions */
 scalar_t__ ICN8505_EVENT_UPDATE1 ; 
 scalar_t__ ICN8505_EVENT_UPDATE2 ; 

__attribute__((used)) static bool icn8505_touch_active(u8 event)
{
	return event == ICN8505_EVENT_UPDATE1 ||
	       event == ICN8505_EVENT_UPDATE2;
}