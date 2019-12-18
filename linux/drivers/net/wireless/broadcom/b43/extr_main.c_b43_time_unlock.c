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
 int /*<<< orphan*/  B43_MACCTL_TBTTHOLD ; 
 int /*<<< orphan*/  B43_MMIO_MACCTL ; 
 int /*<<< orphan*/  b43_maskset32 (struct b43_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_read32 (struct b43_wldev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void b43_time_unlock(struct b43_wldev *dev)
{
	b43_maskset32(dev, B43_MMIO_MACCTL, ~B43_MACCTL_TBTTHOLD, 0);
	/* Commit the write */
	b43_read32(dev, B43_MMIO_MACCTL);
}