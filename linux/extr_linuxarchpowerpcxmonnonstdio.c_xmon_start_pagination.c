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
 scalar_t__ paginate_pos ; 
 int paginate_skipping ; 
 int paginating ; 

void xmon_start_pagination(void)
{
	paginating = true;
	paginate_skipping = false;
	paginate_pos = 0;
}