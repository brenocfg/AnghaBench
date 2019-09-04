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
typedef  int u64 ;
struct clocksource {int dummy; } ;

/* Variables and functions */
 int TIMER_MULTIPLIER ; 
 int os_nsecs () ; 

__attribute__((used)) static u64 timer_read(struct clocksource *cs)
{
	return os_nsecs() / TIMER_MULTIPLIER;
}