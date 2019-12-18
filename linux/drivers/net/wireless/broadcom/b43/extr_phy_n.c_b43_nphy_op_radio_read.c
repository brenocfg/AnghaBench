#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_2__ {int rev; } ;
struct b43_wldev {TYPE_1__ phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_MMIO_RADIO_CONTROL ; 
 int /*<<< orphan*/  B43_MMIO_RADIO_DATA_LOW ; 
 int /*<<< orphan*/  B43_WARN_ON (int) ; 
 int b43_read16 (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_write16f (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u16 b43_nphy_op_radio_read(struct b43_wldev *dev, u16 reg)
{
	/* Register 1 is a 32-bit register. */
	B43_WARN_ON(dev->phy.rev < 7 && reg == 1);

	if (dev->phy.rev >= 7)
		reg |= 0x200; /* Radio 0x2057 */
	else
		reg |= 0x100;

	b43_write16f(dev, B43_MMIO_RADIO_CONTROL, reg);
	return b43_read16(dev, B43_MMIO_RADIO_DATA_LOW);
}