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
typedef  int u32 ;

/* Variables and functions */
 int omap_reserved_systimers ; 

__attribute__((used)) static inline u32 omap_dm_timer_reserved_systimer(int id)
{
	return (omap_reserved_systimers & (1 << (id - 1))) ? 1 : 0;
}