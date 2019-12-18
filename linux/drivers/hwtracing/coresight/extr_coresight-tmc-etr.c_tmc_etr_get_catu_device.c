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
struct tmc_drvdata {struct coresight_device* csdev; } ;
struct coresight_device {TYPE_2__* pdata; } ;
struct TYPE_4__ {int nr_outport; TYPE_1__* conns; } ;
struct TYPE_3__ {struct coresight_device* child_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_CORESIGHT_CATU ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ coresight_is_catu_device (struct coresight_device*) ; 

struct coresight_device *
tmc_etr_get_catu_device(struct tmc_drvdata *drvdata)
{
	int i;
	struct coresight_device *tmp, *etr = drvdata->csdev;

	if (!IS_ENABLED(CONFIG_CORESIGHT_CATU))
		return NULL;

	for (i = 0; i < etr->pdata->nr_outport; i++) {
		tmp = etr->pdata->conns[i].child_dev;
		if (tmp && coresight_is_catu_device(tmp))
			return tmp;
	}

	return NULL;
}