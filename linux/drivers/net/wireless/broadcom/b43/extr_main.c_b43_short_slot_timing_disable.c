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
struct b43_wldev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  b43_set_slot_time (struct b43_wldev*,int) ; 

__attribute__((used)) static void b43_short_slot_timing_disable(struct b43_wldev *dev)
{
	b43_set_slot_time(dev, 20);
}