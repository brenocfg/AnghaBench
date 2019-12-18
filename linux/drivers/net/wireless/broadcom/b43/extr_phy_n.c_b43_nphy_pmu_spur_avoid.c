#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct b43_wldev {TYPE_5__* dev; } ;
struct TYPE_10__ {int bus_type; TYPE_4__* sdev; TYPE_2__* bdev; } ;
struct TYPE_9__ {TYPE_3__* bus; } ;
struct TYPE_8__ {int /*<<< orphan*/  chipco; } ;
struct TYPE_7__ {TYPE_1__* bus; } ;
struct TYPE_6__ {int /*<<< orphan*/  drv_cc; } ;

/* Variables and functions */
#define  B43_BUS_BCMA 129 
#define  B43_BUS_SSB 128 
 int /*<<< orphan*/  bcma_pmu_spuravoid_pllupdate (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ssb_pmu_spuravoid_pllupdate (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void b43_nphy_pmu_spur_avoid(struct b43_wldev *dev, bool avoid)
{
	switch (dev->dev->bus_type) {
#ifdef CONFIG_B43_BCMA
	case B43_BUS_BCMA:
		bcma_pmu_spuravoid_pllupdate(&dev->dev->bdev->bus->drv_cc,
					     avoid);
		break;
#endif
#ifdef CONFIG_B43_SSB
	case B43_BUS_SSB:
		ssb_pmu_spuravoid_pllupdate(&dev->dev->sdev->bus->chipco,
					    avoid);
		break;
#endif
	}
}