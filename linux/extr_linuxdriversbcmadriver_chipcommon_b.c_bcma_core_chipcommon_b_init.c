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
struct bcma_drv_cc_b {int setup_done; int /*<<< orphan*/  mii; TYPE_1__* core; } ;
struct TYPE_2__ {int /*<<< orphan*/ * addr_s; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCMA_CORE_SIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ioremap_nocache (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int bcma_core_chipcommon_b_init(struct bcma_drv_cc_b *ccb)
{
	if (ccb->setup_done)
		return 0;

	ccb->setup_done = 1;
	ccb->mii = ioremap_nocache(ccb->core->addr_s[1], BCMA_CORE_SIZE);
	if (!ccb->mii)
		return -ENOMEM;

	return 0;
}