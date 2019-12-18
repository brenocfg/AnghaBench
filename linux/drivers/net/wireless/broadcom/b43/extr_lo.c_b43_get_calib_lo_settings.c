#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* g; } ;
struct b43_wldev {TYPE_2__ phy; } ;
struct b43_txpower_lo_control {int /*<<< orphan*/  calib_list; } ;
struct b43_rfatt {int dummy; } ;
struct b43_lo_calib {int /*<<< orphan*/  list; } ;
struct b43_bbatt {int dummy; } ;
struct TYPE_3__ {struct b43_txpower_lo_control* lo_control; } ;

/* Variables and functions */
 struct b43_lo_calib* b43_calibrate_lo_setting (struct b43_wldev*,struct b43_bbatt const*,struct b43_rfatt const*) ; 
 struct b43_lo_calib* b43_find_lo_calib (struct b43_txpower_lo_control*,struct b43_bbatt const*,struct b43_rfatt const*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
struct b43_lo_calib *b43_get_calib_lo_settings(struct b43_wldev *dev,
					       const struct b43_bbatt *bbatt,
					       const struct b43_rfatt *rfatt)
{
	struct b43_txpower_lo_control *lo = dev->phy.g->lo_control;
	struct b43_lo_calib *c;

	c = b43_find_lo_calib(lo, bbatt, rfatt);
	if (c)
		return c;
	/* Not in the list of calibrated LO settings.
	 * Calibrate it now. */
	c = b43_calibrate_lo_setting(dev, bbatt, rfatt);
	if (!c)
		return NULL;
	list_add(&c->list, &lo->calib_list);

	return c;
}