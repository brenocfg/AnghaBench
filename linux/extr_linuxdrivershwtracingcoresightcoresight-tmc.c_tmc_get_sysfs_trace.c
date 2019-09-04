#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tmc_drvdata {int config_type; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
#define  TMC_CONFIG_TYPE_ETB 130 
#define  TMC_CONFIG_TYPE_ETF 129 
#define  TMC_CONFIG_TYPE_ETR 128 
 int /*<<< orphan*/  tmc_etb_get_sysfs_trace (struct tmc_drvdata*,int /*<<< orphan*/ ,size_t,char**) ; 
 int /*<<< orphan*/  tmc_etr_get_sysfs_trace (struct tmc_drvdata*,int /*<<< orphan*/ ,size_t,char**) ; 

__attribute__((used)) static inline ssize_t tmc_get_sysfs_trace(struct tmc_drvdata *drvdata,
					  loff_t pos, size_t len, char **bufpp)
{
	switch (drvdata->config_type) {
	case TMC_CONFIG_TYPE_ETB:
	case TMC_CONFIG_TYPE_ETF:
		return tmc_etb_get_sysfs_trace(drvdata, pos, len, bufpp);
	case TMC_CONFIG_TYPE_ETR:
		return tmc_etr_get_sysfs_trace(drvdata, pos, len, bufpp);
	}

	return -EINVAL;
}