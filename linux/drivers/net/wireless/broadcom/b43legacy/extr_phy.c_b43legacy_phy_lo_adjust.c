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
struct b43legacy_wldev {int dummy; } ;
struct b43legacy_lopair {int dummy; } ;

/* Variables and functions */
 struct b43legacy_lopair* b43legacy_current_lopair (struct b43legacy_wldev*) ; 
 struct b43legacy_lopair* b43legacy_find_lopair (struct b43legacy_wldev*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43legacy_lo_write (struct b43legacy_wldev*,struct b43legacy_lopair*) ; 

void b43legacy_phy_lo_adjust(struct b43legacy_wldev *dev, int fixed)
{
	struct b43legacy_lopair *pair;

	if (fixed) {
		/* Use fixed values. Only for initialization. */
		pair = b43legacy_find_lopair(dev, 2, 3, 0);
	} else
		pair = b43legacy_current_lopair(dev);
	b43legacy_lo_write(dev, pair);
}