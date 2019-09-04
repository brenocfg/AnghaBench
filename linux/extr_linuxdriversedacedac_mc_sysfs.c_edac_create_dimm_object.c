#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct mem_ctl_info {int /*<<< orphan*/  dev; scalar_t__ csbased; int /*<<< orphan*/  bus; } ;
struct TYPE_6__ {int /*<<< orphan*/ * parent; int /*<<< orphan*/  bus; int /*<<< orphan*/ * type; } ;
struct dimm_info {TYPE_1__ dev; struct mem_ctl_info* mci; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_name (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_1__*,struct dimm_info*) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,char*,int) ; 
 int device_add (TYPE_1__*) ; 
 int /*<<< orphan*/  device_initialize (TYPE_1__*) ; 
 int /*<<< orphan*/  dimm_attr_type ; 
 int /*<<< orphan*/  edac_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_forbid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int edac_create_dimm_object(struct mem_ctl_info *mci,
				   struct dimm_info *dimm,
				   int index)
{
	int err;
	dimm->mci = mci;

	dimm->dev.type = &dimm_attr_type;
	dimm->dev.bus = mci->bus;
	device_initialize(&dimm->dev);

	dimm->dev.parent = &mci->dev;
	if (mci->csbased)
		dev_set_name(&dimm->dev, "rank%d", index);
	else
		dev_set_name(&dimm->dev, "dimm%d", index);
	dev_set_drvdata(&dimm->dev, dimm);
	pm_runtime_forbid(&mci->dev);

	err =  device_add(&dimm->dev);

	edac_dbg(0, "creating rank/dimm device %s\n", dev_name(&dimm->dev));

	return err;
}