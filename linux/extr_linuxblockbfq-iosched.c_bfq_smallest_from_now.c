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
 unsigned long MAX_JIFFY_OFFSET ; 
 unsigned long jiffies ; 

__attribute__((used)) static unsigned long bfq_smallest_from_now(void)
{
	return jiffies - MAX_JIFFY_OFFSET;
}