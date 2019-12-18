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
struct b43legacy_phy {int* nrssi; int nrssislope; int* nrssi_lt; } ;
struct b43legacy_wldev {struct b43legacy_phy phy; } ;
typedef  int s32 ;
typedef  int s16 ;

/* Variables and functions */
 int clamp_val (int,int /*<<< orphan*/ ,int) ; 

void b43legacy_nrssi_mem_update(struct b43legacy_wldev *dev)
{
	struct b43legacy_phy *phy = &dev->phy;
	s16 i;
	s16 delta;
	s32 tmp;

	delta = 0x1F - phy->nrssi[0];
	for (i = 0; i < 64; i++) {
		tmp = (i - delta) * phy->nrssislope;
		tmp /= 0x10000;
		tmp += 0x3A;
		tmp = clamp_val(tmp, 0, 0x3F);
		phy->nrssi_lt[i] = tmp;
	}
}