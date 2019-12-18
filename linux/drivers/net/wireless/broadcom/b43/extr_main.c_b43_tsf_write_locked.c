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
typedef  int u64 ;
typedef  int u32 ;
struct b43_wldev {TYPE_1__* dev; } ;
struct TYPE_2__ {int core_rev; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_MMIO_REV3PLUS_TSF_HIGH ; 
 int /*<<< orphan*/  B43_MMIO_REV3PLUS_TSF_LOW ; 
 int /*<<< orphan*/  B43_WARN_ON (int) ; 
 int /*<<< orphan*/  b43_write32 (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void b43_tsf_write_locked(struct b43_wldev *dev, u64 tsf)
{
	u32 low, high;

	B43_WARN_ON(dev->dev->core_rev < 3);

	low = tsf;
	high = (tsf >> 32);
	/* The hardware guarantees us an atomic write, if we
	 * write the low register first. */
	b43_write32(dev, B43_MMIO_REV3PLUS_TSF_LOW, low);
	b43_write32(dev, B43_MMIO_REV3PLUS_TSF_HIGH, high);
}