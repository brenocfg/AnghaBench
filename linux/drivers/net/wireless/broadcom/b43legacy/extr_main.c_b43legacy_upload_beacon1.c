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
struct b43legacy_wldev {struct b43legacy_wl* wl; } ;
struct b43legacy_wl {int beacon1_uploaded; } ;

/* Variables and functions */
 int /*<<< orphan*/  b43legacy_write_beacon_template (struct b43legacy_wldev*,int,int) ; 

__attribute__((used)) static void b43legacy_upload_beacon1(struct b43legacy_wldev *dev)
{
	struct b43legacy_wl *wl = dev->wl;

	if (wl->beacon1_uploaded)
		return;
	b43legacy_write_beacon_template(dev, 0x468, 0x1A);
	wl->beacon1_uploaded = true;
}