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
struct sp_device {struct ccp_device* ccp_data; scalar_t__ io_map; int /*<<< orphan*/  use_tasklet; TYPE_1__* dev_vdata; struct device* dev; } ;
struct device {int dummy; } ;
struct ccp_vdata {TYPE_2__* perform; int /*<<< orphan*/  (* setup ) (struct ccp_device*) ;scalar_t__ offset; int /*<<< orphan*/  version; } ;
struct ccp_device {struct ccp_vdata* vdata; scalar_t__ io_regs; int /*<<< orphan*/  use_tasklet; } ;
struct TYPE_4__ {int (* init ) (struct ccp_device*) ;} ;
struct TYPE_3__ {scalar_t__ ccp_vdata; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 struct ccp_device* ccp_alloc_struct (struct sp_device*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_notice (struct device*,char*) ; 
 int /*<<< orphan*/  stub1 (struct ccp_device*) ; 
 int stub2 (struct ccp_device*) ; 

int ccp_dev_init(struct sp_device *sp)
{
	struct device *dev = sp->dev;
	struct ccp_device *ccp;
	int ret;

	ret = -ENOMEM;
	ccp = ccp_alloc_struct(sp);
	if (!ccp)
		goto e_err;
	sp->ccp_data = ccp;

	ccp->vdata = (struct ccp_vdata *)sp->dev_vdata->ccp_vdata;
	if (!ccp->vdata || !ccp->vdata->version) {
		ret = -ENODEV;
		dev_err(dev, "missing driver data\n");
		goto e_err;
	}

	ccp->use_tasklet = sp->use_tasklet;

	ccp->io_regs = sp->io_map + ccp->vdata->offset;
	if (ccp->vdata->setup)
		ccp->vdata->setup(ccp);

	ret = ccp->vdata->perform->init(ccp);
	if (ret)
		goto e_err;

	dev_notice(dev, "ccp enabled\n");

	return 0;

e_err:
	sp->ccp_data = NULL;

	dev_notice(dev, "ccp initialization failed\n");

	return ret;
}