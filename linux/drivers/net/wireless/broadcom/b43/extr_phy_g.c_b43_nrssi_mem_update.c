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
struct TYPE_2__ {struct b43_phy_g* g; } ;
struct b43_wldev {TYPE_1__ phy; } ;
struct b43_phy_g {int* nrssi; int nrssislope; int* nrssi_lt; } ;
typedef  int s32 ;
typedef  int s16 ;

/* Variables and functions */
 int clamp_val (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void b43_nrssi_mem_update(struct b43_wldev *dev)
{
	struct b43_phy_g *gphy = dev->phy.g;
	s16 i, delta;
	s32 tmp;

	delta = 0x1F - gphy->nrssi[0];
	for (i = 0; i < 64; i++) {
		tmp = (i - delta) * gphy->nrssislope;
		tmp /= 0x10000;
		tmp += 0x3A;
		tmp = clamp_val(tmp, 0, 0x3F);
		gphy->nrssi_lt[i] = tmp;
	}
}