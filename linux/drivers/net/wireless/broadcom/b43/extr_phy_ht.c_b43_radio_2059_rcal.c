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
struct b43_wldev {int /*<<< orphan*/  wl; } ;

/* Variables and functions */
 int R2059_C3 ; 
 int R2059_RCAL_CONFIG ; 
 int R2059_RCAL_STATUS ; 
 int /*<<< orphan*/  b43_radio_mask (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_radio_maskset (struct b43_wldev*,int,int,int) ; 
 int /*<<< orphan*/  b43_radio_set (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_radio_wait_value (struct b43_wldev*,int,int,int,int,int) ; 
 int /*<<< orphan*/  b43err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void b43_radio_2059_rcal(struct b43_wldev *dev)
{
	/* Enable */
	b43_radio_set(dev, R2059_C3 | R2059_RCAL_CONFIG, 0x1);
	usleep_range(10, 20);

	b43_radio_set(dev, R2059_C3 | 0x0BF, 0x1);
	b43_radio_maskset(dev, R2059_C3 | 0x19B, 0x3, 0x2);

	/* Start */
	b43_radio_set(dev, R2059_C3 | R2059_RCAL_CONFIG, 0x2);
	usleep_range(100, 200);

	/* Stop */
	b43_radio_mask(dev, R2059_C3 | R2059_RCAL_CONFIG, ~0x2);

	if (!b43_radio_wait_value(dev, R2059_C3 | R2059_RCAL_STATUS, 1, 1, 100,
				  1000000))
		b43err(dev->wl, "Radio 0x2059 rcal timeout\n");

	/* Disable */
	b43_radio_mask(dev, R2059_C3 | R2059_RCAL_CONFIG, ~0x1);

	b43_radio_set(dev, 0xa, 0x60);
}