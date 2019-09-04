#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct csc_data {scalar_t__ base; TYPE_2__* res; TYPE_1__* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  start; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 scalar_t__ CSC_CSC00 ; 
 scalar_t__ CSC_CSC01 ; 
 scalar_t__ CSC_CSC02 ; 
 scalar_t__ CSC_CSC03 ; 
 scalar_t__ CSC_CSC04 ; 
 scalar_t__ CSC_CSC05 ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,char*,...) ; 
 int /*<<< orphan*/  ioread32 (scalar_t__) ; 

void csc_dump_regs(struct csc_data *csc)
{
	struct device *dev = &csc->pdev->dev;

#define DUMPREG(r) dev_dbg(dev, "%-35s %08x\n", #r, \
	ioread32(csc->base + CSC_##r))

	dev_dbg(dev, "CSC Registers @ %pa:\n", &csc->res->start);

	DUMPREG(CSC00);
	DUMPREG(CSC01);
	DUMPREG(CSC02);
	DUMPREG(CSC03);
	DUMPREG(CSC04);
	DUMPREG(CSC05);

#undef DUMPREG
}