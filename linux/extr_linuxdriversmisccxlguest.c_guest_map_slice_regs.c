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
struct cxl_afu {int /*<<< orphan*/  slice; int /*<<< orphan*/  dev; TYPE_1__* guest; int /*<<< orphan*/  p2n_mmio; } ;
struct TYPE_2__ {int /*<<< orphan*/  p2n_size; int /*<<< orphan*/  p2n_phys; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int guest_map_slice_regs(struct cxl_afu *afu)
{
	if (!(afu->p2n_mmio = ioremap(afu->guest->p2n_phys, afu->guest->p2n_size))) {
		dev_err(&afu->dev, "Error mapping AFU(%d) MMIO regions\n",
			afu->slice);
		return -ENOMEM;
	}
	return 0;
}