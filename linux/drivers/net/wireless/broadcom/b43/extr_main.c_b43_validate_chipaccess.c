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
typedef  int u32 ;
struct b43_wldev {int /*<<< orphan*/  wl; TYPE_1__* dev; } ;
struct TYPE_2__ {int core_rev; } ;

/* Variables and functions */
 int B43_MACCTL_GMODE ; 
 int B43_MACCTL_IHR_ENABLED ; 
 int /*<<< orphan*/  B43_MMIO_MACCTL ; 
 int /*<<< orphan*/  B43_MMIO_TSF_CFP_START ; 
 int /*<<< orphan*/  B43_MMIO_TSF_CFP_START_HIGH ; 
 int /*<<< orphan*/  B43_MMIO_TSF_CFP_START_LOW ; 
 int /*<<< orphan*/  B43_SHM_SHARED ; 
 int ENODEV ; 
 int b43_read16 (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int b43_read32 (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int b43_shm_read16 (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int b43_shm_read32 (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_shm_write16 (struct b43_wldev*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  b43_shm_write32 (struct b43_wldev*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  b43_write16 (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_write32 (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  b43warn (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int b43_validate_chipaccess(struct b43_wldev *dev)
{
	u32 v, backup0, backup4;

	backup0 = b43_shm_read32(dev, B43_SHM_SHARED, 0);
	backup4 = b43_shm_read32(dev, B43_SHM_SHARED, 4);

	/* Check for read/write and endianness problems. */
	b43_shm_write32(dev, B43_SHM_SHARED, 0, 0x55AAAA55);
	if (b43_shm_read32(dev, B43_SHM_SHARED, 0) != 0x55AAAA55)
		goto error;
	b43_shm_write32(dev, B43_SHM_SHARED, 0, 0xAA5555AA);
	if (b43_shm_read32(dev, B43_SHM_SHARED, 0) != 0xAA5555AA)
		goto error;

	/* Check if unaligned 32bit SHM_SHARED access works properly.
	 * However, don't bail out on failure, because it's noncritical. */
	b43_shm_write16(dev, B43_SHM_SHARED, 0, 0x1122);
	b43_shm_write16(dev, B43_SHM_SHARED, 2, 0x3344);
	b43_shm_write16(dev, B43_SHM_SHARED, 4, 0x5566);
	b43_shm_write16(dev, B43_SHM_SHARED, 6, 0x7788);
	if (b43_shm_read32(dev, B43_SHM_SHARED, 2) != 0x55663344)
		b43warn(dev->wl, "Unaligned 32bit SHM read access is broken\n");
	b43_shm_write32(dev, B43_SHM_SHARED, 2, 0xAABBCCDD);
	if (b43_shm_read16(dev, B43_SHM_SHARED, 0) != 0x1122 ||
	    b43_shm_read16(dev, B43_SHM_SHARED, 2) != 0xCCDD ||
	    b43_shm_read16(dev, B43_SHM_SHARED, 4) != 0xAABB ||
	    b43_shm_read16(dev, B43_SHM_SHARED, 6) != 0x7788)
		b43warn(dev->wl, "Unaligned 32bit SHM write access is broken\n");

	b43_shm_write32(dev, B43_SHM_SHARED, 0, backup0);
	b43_shm_write32(dev, B43_SHM_SHARED, 4, backup4);

	if ((dev->dev->core_rev >= 3) && (dev->dev->core_rev <= 10)) {
		/* The 32bit register shadows the two 16bit registers
		 * with update sideeffects. Validate this. */
		b43_write16(dev, B43_MMIO_TSF_CFP_START, 0xAAAA);
		b43_write32(dev, B43_MMIO_TSF_CFP_START, 0xCCCCBBBB);
		if (b43_read16(dev, B43_MMIO_TSF_CFP_START_LOW) != 0xBBBB)
			goto error;
		if (b43_read16(dev, B43_MMIO_TSF_CFP_START_HIGH) != 0xCCCC)
			goto error;
	}
	b43_write32(dev, B43_MMIO_TSF_CFP_START, 0);

	v = b43_read32(dev, B43_MMIO_MACCTL);
	v |= B43_MACCTL_GMODE;
	if (v != (B43_MACCTL_GMODE | B43_MACCTL_IHR_ENABLED))
		goto error;

	return 0;
error:
	b43err(dev->wl, "Failed to validate the chipaccess\n");
	return -ENODEV;
}