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
struct sc_data {scalar_t__ base; TYPE_2__* res; TYPE_1__* pdev; } ;
struct device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  start; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 scalar_t__ CFG_SC0 ; 
 scalar_t__ CFG_SC1 ; 
 scalar_t__ CFG_SC10 ; 
 scalar_t__ CFG_SC11 ; 
 scalar_t__ CFG_SC12 ; 
 scalar_t__ CFG_SC13 ; 
 scalar_t__ CFG_SC17 ; 
 scalar_t__ CFG_SC18 ; 
 scalar_t__ CFG_SC19 ; 
 scalar_t__ CFG_SC2 ; 
 scalar_t__ CFG_SC20 ; 
 scalar_t__ CFG_SC21 ; 
 scalar_t__ CFG_SC22 ; 
 scalar_t__ CFG_SC23 ; 
 scalar_t__ CFG_SC24 ; 
 scalar_t__ CFG_SC25 ; 
 scalar_t__ CFG_SC3 ; 
 scalar_t__ CFG_SC4 ; 
 scalar_t__ CFG_SC5 ; 
 scalar_t__ CFG_SC6 ; 
 scalar_t__ CFG_SC8 ; 
 scalar_t__ CFG_SC9 ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,char*,...) ; 
 int /*<<< orphan*/  ioread32 (scalar_t__) ; 

void sc_dump_regs(struct sc_data *sc)
{
	struct device *dev = &sc->pdev->dev;

#define DUMPREG(r) dev_dbg(dev, "%-35s %08x\n", #r, \
	ioread32(sc->base + CFG_##r))

	dev_dbg(dev, "SC Registers @ %pa:\n", &sc->res->start);

	DUMPREG(SC0);
	DUMPREG(SC1);
	DUMPREG(SC2);
	DUMPREG(SC3);
	DUMPREG(SC4);
	DUMPREG(SC5);
	DUMPREG(SC6);
	DUMPREG(SC8);
	DUMPREG(SC9);
	DUMPREG(SC10);
	DUMPREG(SC11);
	DUMPREG(SC12);
	DUMPREG(SC13);
	DUMPREG(SC17);
	DUMPREG(SC18);
	DUMPREG(SC19);
	DUMPREG(SC20);
	DUMPREG(SC21);
	DUMPREG(SC22);
	DUMPREG(SC23);
	DUMPREG(SC24);
	DUMPREG(SC25);

#undef DUMPREG
}