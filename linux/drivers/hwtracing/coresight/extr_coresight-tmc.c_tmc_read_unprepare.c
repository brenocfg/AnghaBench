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
struct tmc_drvdata {int config_type; TYPE_1__* csdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
#define  TMC_CONFIG_TYPE_ETB 130 
#define  TMC_CONFIG_TYPE_ETF 129 
#define  TMC_CONFIG_TYPE_ETR 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int tmc_read_unprepare_etb (struct tmc_drvdata*) ; 
 int tmc_read_unprepare_etr (struct tmc_drvdata*) ; 

__attribute__((used)) static int tmc_read_unprepare(struct tmc_drvdata *drvdata)
{
	int ret = 0;

	switch (drvdata->config_type) {
	case TMC_CONFIG_TYPE_ETB:
	case TMC_CONFIG_TYPE_ETF:
		ret = tmc_read_unprepare_etb(drvdata);
		break;
	case TMC_CONFIG_TYPE_ETR:
		ret = tmc_read_unprepare_etr(drvdata);
		break;
	default:
		ret = -EINVAL;
	}

	if (!ret)
		dev_dbg(&drvdata->csdev->dev, "TMC read end\n");

	return ret;
}