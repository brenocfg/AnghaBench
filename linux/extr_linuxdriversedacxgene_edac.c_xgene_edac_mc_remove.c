#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xgene_edac_mc_ctx {TYPE_1__* mci; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  edac_mc_del_mc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  edac_mc_free (TYPE_1__*) ; 
 int /*<<< orphan*/  xgene_edac_mc_irq_ctl (TYPE_1__*,int) ; 

__attribute__((used)) static int xgene_edac_mc_remove(struct xgene_edac_mc_ctx *mcu)
{
	xgene_edac_mc_irq_ctl(mcu->mci, false);
	edac_mc_del_mc(&mcu->mci->dev);
	edac_mc_free(mcu->mci);
	return 0;
}