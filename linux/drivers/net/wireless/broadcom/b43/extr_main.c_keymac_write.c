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
typedef  int u8 ;
typedef  int u32 ;
struct b43_wldev {int dummy; } ;

/* Variables and functions */
 int B43_NR_GROUP_KEYS ; 
 int B43_NR_PAIRWISE_KEYS ; 
 int /*<<< orphan*/  B43_SHM_RCMTA ; 
 int /*<<< orphan*/  B43_WARN_ON (int) ; 
 scalar_t__ b43_new_kidx_api (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_shm_write16 (struct b43_wldev*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  b43_shm_write32 (struct b43_wldev*,int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static void keymac_write(struct b43_wldev *dev, u8 index, const u8 *addr)
{
	u32 addrtmp[2] = { 0, 0, };
	u8 pairwise_keys_start = B43_NR_GROUP_KEYS * 2;

	if (b43_new_kidx_api(dev))
		pairwise_keys_start = B43_NR_GROUP_KEYS;

	B43_WARN_ON(index < pairwise_keys_start);
	/* We have four default TX keys and possibly four default RX keys.
	 * Physical mac 0 is mapped to physical key 4 or 8, depending
	 * on the firmware version.
	 * So we must adjust the index here.
	 */
	index -= pairwise_keys_start;
	B43_WARN_ON(index >= B43_NR_PAIRWISE_KEYS);

	if (addr) {
		addrtmp[0] = addr[0];
		addrtmp[0] |= ((u32) (addr[1]) << 8);
		addrtmp[0] |= ((u32) (addr[2]) << 16);
		addrtmp[0] |= ((u32) (addr[3]) << 24);
		addrtmp[1] = addr[4];
		addrtmp[1] |= ((u32) (addr[5]) << 8);
	}

	/* Receive match transmitter address (RCMTA) mechanism */
	b43_shm_write32(dev, B43_SHM_RCMTA,
			(index * 2) + 0, addrtmp[0]);
	b43_shm_write16(dev, B43_SHM_RCMTA,
			(index * 2) + 1, addrtmp[1]);
}