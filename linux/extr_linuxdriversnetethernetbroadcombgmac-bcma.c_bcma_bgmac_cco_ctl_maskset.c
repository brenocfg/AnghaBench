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
 int /*<<< orphan*/  bcma_chipco_chipctl_maskset (struct bcma_drv_cc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcma_bgmac_cco_ctl_maskset(struct bgmac *bgmac, u32 offset,
				       u32 mask, u32 set)
{
	struct bcma_drv_cc *cc = &bgmac->bcma.core->bus->drv_cc;

	bcma_chipco_chipctl_maskset(cc, offset, mask, set);
}