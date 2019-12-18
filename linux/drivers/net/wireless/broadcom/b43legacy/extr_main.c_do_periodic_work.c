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
struct b43legacy_wldev {unsigned int periodic_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  b43legacy_periodic_every120sec (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_periodic_every15sec (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_periodic_every30sec (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_periodic_every60sec (struct b43legacy_wldev*) ; 

__attribute__((used)) static void do_periodic_work(struct b43legacy_wldev *dev)
{
	unsigned int state;

	state = dev->periodic_state;
	if (state % 8 == 0)
		b43legacy_periodic_every120sec(dev);
	if (state % 4 == 0)
		b43legacy_periodic_every60sec(dev);
	if (state % 2 == 0)
		b43legacy_periodic_every30sec(dev);
	b43legacy_periodic_every15sec(dev);
}