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

/* Variables and functions */
 int /*<<< orphan*/  b43legacy_release_firmware (struct b43legacy_wldev*) ; 

__attribute__((used)) static void b43legacy_wireless_core_detach(struct b43legacy_wldev *dev)
{
	/* We release firmware that late to not be required to re-request
	 * is all the time when we reinit the core. */
	b43legacy_release_firmware(dev);
}