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
struct genwqe_dev {TYPE_1__* ffdc; } ;
struct TYPE_2__ {int /*<<< orphan*/ * regs; } ;

/* Variables and functions */
 unsigned int GENWQE_DBG_UNITS ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void genwqe_ffdc_buffs_free(struct genwqe_dev *cd)
{
	unsigned int type;

	for (type = 0; type < GENWQE_DBG_UNITS; type++) {
		kfree(cd->ffdc[type].regs);
		cd->ffdc[type].regs = NULL;
	}
}