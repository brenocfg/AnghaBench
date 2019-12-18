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
typedef  int u16 ;
struct b43legacy_wldev {int dummy; } ;

/* Variables and functions */
 int B43legacy_MACCTL_BE ; 
 int /*<<< orphan*/  B43legacy_MMIO_MACCTL ; 
 int /*<<< orphan*/  B43legacy_MMIO_RAM_CONTROL ; 
 int /*<<< orphan*/  B43legacy_MMIO_RAM_DATA ; 
 int /*<<< orphan*/  B43legacy_WARN_ON (int) ; 
 int b43legacy_read32 (struct b43legacy_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43legacy_write32 (struct b43legacy_wldev*,int /*<<< orphan*/ ,int) ; 
 int swab32 (int) ; 

__attribute__((used)) static void b43legacy_ram_write(struct b43legacy_wldev *dev, u16 offset,
				u32 val)
{
	u32 status;

	B43legacy_WARN_ON(offset % 4 != 0);

	status = b43legacy_read32(dev, B43legacy_MMIO_MACCTL);
	if (status & B43legacy_MACCTL_BE)
		val = swab32(val);

	b43legacy_write32(dev, B43legacy_MMIO_RAM_CONTROL, offset);
	b43legacy_write32(dev, B43legacy_MMIO_RAM_DATA, val);
}