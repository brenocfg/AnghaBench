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
 int QUEUE_STAT2_OVERFLOW ; 
 int __qmgr_get_stat2 (unsigned int) ; 

int qmgr_stat_overflow(unsigned int queue)
{
	return __qmgr_get_stat2(queue) & QUEUE_STAT2_OVERFLOW;
}