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
struct vimc_platform_data {int /*<<< orphan*/  entity_name; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct vimc_device {TYPE_3__* pipe_cfg; TYPE_1__ pdev; int /*<<< orphan*/ * subdevs; } ;
struct component_match {int dummy; } ;
typedef  int /*<<< orphan*/  pdata ;
struct TYPE_6__ {int num_ents; TYPE_2__* ents; } ;
struct TYPE_5__ {scalar_t__ name; int /*<<< orphan*/  drv; } ;

/* Variables and functions */
 struct component_match* ERR_CAST (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLATFORM_DEVID_AUTO ; 
 int /*<<< orphan*/  component_match_add (int /*<<< orphan*/ *,struct component_match**,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_device_register_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vimc_platform_data*,int) ; 
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  vimc_comp_compare ; 

__attribute__((used)) static struct component_match *vimc_add_subdevs(struct vimc_device *vimc)
{
	struct component_match *match = NULL;
	struct vimc_platform_data pdata;
	int i;

	for (i = 0; i < vimc->pipe_cfg->num_ents; i++) {
		dev_dbg(&vimc->pdev.dev, "new pdev for %s\n",
			vimc->pipe_cfg->ents[i].drv);

		strlcpy(pdata.entity_name, vimc->pipe_cfg->ents[i].name,
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
				    (void *)vimc->pipe_cfg->ents[i].name);
	}

	return match;
}