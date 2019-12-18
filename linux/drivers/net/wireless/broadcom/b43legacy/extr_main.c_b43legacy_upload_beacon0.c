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
struct b43legacy_wl {int beacon0_uploaded; } ;

/* Variables and functions */
 int /*<<< orphan*/ * __b43legacy_ratetable ; 
 int /*<<< orphan*/  b43legacy_write_beacon_template (struct b43legacy_wldev*,int,int) ; 
 int /*<<< orphan*/  b43legacy_write_probe_resp_template (struct b43legacy_wldev*,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void b43legacy_upload_beacon0(struct b43legacy_wldev *dev)
{
	struct b43legacy_wl *wl = dev->wl;

	if (wl->beacon0_uploaded)
		return;
	b43legacy_write_beacon_template(dev, 0x68, 0x18);
	/* FIXME: Probe resp upload doesn't really belong here,
	 *        but we don't use that feature anyway. */
	b43legacy_write_probe_resp_template(dev, 0x268, 0x4A,
				      &__b43legacy_ratetable[3]);
	wl->beacon0_uploaded = true;
}