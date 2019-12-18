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
typedef  scalar_t__ u16 ;
struct b43_wldev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_MMIO_SHM_DATA ; 
 int /*<<< orphan*/  B43_MMIO_SHM_DATA_UNALIGNED ; 
 scalar_t__ B43_SHM_SHARED ; 
 int /*<<< orphan*/  B43_WARN_ON (scalar_t__) ; 
 int b43_read16 (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int b43_read32 (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_shm_control_word (struct b43_wldev*,scalar_t__,scalar_t__) ; 

u32 b43_shm_read32(struct b43_wldev *dev, u16 routing, u16 offset)
{
	u32 ret;

	if (routing == B43_SHM_SHARED) {
		B43_WARN_ON(offset & 0x0001);
		if (offset & 0x0003) {
			/* Unaligned access */
			b43_shm_control_word(dev, routing, offset >> 2);
			ret = b43_read16(dev, B43_MMIO_SHM_DATA_UNALIGNED);
			b43_shm_control_word(dev, routing, (offset >> 2) + 1);
			ret |= ((u32)b43_read16(dev, B43_MMIO_SHM_DATA)) << 16;

			goto out;
		}
		offset >>= 2;
	}
	b43_shm_control_word(dev, routing, offset);
	ret = b43_read32(dev, B43_MMIO_SHM_DATA);
out:
	return ret;
}