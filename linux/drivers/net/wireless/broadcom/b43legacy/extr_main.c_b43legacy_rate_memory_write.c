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
typedef  int u16 ;
struct b43legacy_wldev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43legacy_SHM_SHARED ; 
 int b43legacy_plcp_get_ratecode_cck (int) ; 
 int b43legacy_plcp_get_ratecode_ofdm (int) ; 
 int /*<<< orphan*/  b43legacy_shm_read16 (struct b43legacy_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43legacy_shm_write16 (struct b43legacy_wldev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void b43legacy_rate_memory_write(struct b43legacy_wldev *dev,
					u16 rate,
					int is_ofdm)
{
	u16 offset;

	if (is_ofdm) {
		offset = 0x480;
		offset += (b43legacy_plcp_get_ratecode_ofdm(rate) & 0x000F) * 2;
	} else {
		offset = 0x4C0;
		offset += (b43legacy_plcp_get_ratecode_cck(rate) & 0x000F) * 2;
	}
	b43legacy_shm_write16(dev, B43legacy_SHM_SHARED, offset + 0x20,
			      b43legacy_shm_read16(dev,
			      B43legacy_SHM_SHARED, offset));
}