#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct vimc_platform_data {int /*<<< orphan*/  entity_name; } ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;
struct vimc_device {TYPE_4__** subdevs; TYPE_3__ pdev; TYPE_2__* pipe_cfg; } ;
struct component_match {int dummy; } ;
typedef  int /*<<< orphan*/  pdata ;
struct TYPE_11__ {int /*<<< orphan*/  dev; } ;
struct TYPE_9__ {int num_ents; TYPE_1__* ents; } ;
struct TYPE_8__ {int /*<<< orphan*/  drv; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct component_match* ERR_CAST (TYPE_4__*) ; 
 scalar_t__ IS_ERR (TYPE_4__*) ; 
 int /*<<< orphan*/  PLATFORM_DEVID_AUTO ; 
 int /*<<< orphan*/  component_match_add (int /*<<< orphan*/ *,struct component_match**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 TYPE_4__* platform_device_register_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vimc_platform_data*,int) ; 
 int /*<<< orphan*/  platform_device_unregister (TYPE_4__*) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vimc_comp_compare ; 

__attribute__((used)) static struct component_match *vimc_add_subdevs(struct vimc_device *vimc)
{
	struct component_match *match = NULL;
	struct vimc_platform_data pdata;
	int i;

	for (i = 0; i < vimc->pipe_cfg->num_ents; i++) {
		dev_dbg(&vimc->pdev.dev, "new pdev for %s\n",
			vimc->pipe_cfg->ents[i].drv);

		strscpy(pdata.entity_name, vimc->pipe_cfg->ents[i].name,
			sizeof(pdata.entity_name));

		vimc->subdevs[i] = platform_device_register_data(&vimc->pdev.dev,
						vimc->pipe_cfg->ents[i].drv,
						PLATFORM_DEVID_AUTO,
						&pdata,
						sizeof(pdata));
		if (IS_ERR(vimc->subdevs[i])) {
			match = ERR_CAST(vimc->subdevs[i]);
			while (--i >= 0)
				platform_device_unregister(vimc->subdevs[i]);

			return match;
		}

		component_match_add(&vimc->pdev.dev, &match, vimc_comp_compare,
				    &vimc->subdevs[i]->dev);
	}

	return match;
}