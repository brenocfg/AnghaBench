#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_6__ {TYPE_2__* core; } ;
struct bgmac {TYPE_3__ bcma; } ;
struct bcma_drv_cc {int dummy; } ;
struct TYPE_5__ {TYPE_1__* bus; } ;
struct TYPE_4__ {struct bcma_drv_cc drv_cc; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcma_pmu_get_bus_clock (struct bcma_drv_cc*) ; 

__attribute__((used)) static u32 bcma_bgmac_get_bus_clock(struct bgmac *bgmac)
{
	struct bcma_drv_cc *cc = &bgmac->bcma.core->bus->drv_cc;

	return bcma_pmu_get_bus_clock(cc);
}