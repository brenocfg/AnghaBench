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
typedef  int u32 ;
struct etmv4_config {int /*<<< orphan*/ * addr_type; } ;
struct etmv4_drvdata {int nr_addr_cmp; struct etmv4_config config; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSPC ; 
 int /*<<< orphan*/  ETM_ADDR_TYPE_NONE ; 
#define  ETM_ADDR_TYPE_RANGE 130 
#define  ETM_ADDR_TYPE_START 129 
#define  ETM_ADDR_TYPE_STOP 128 

__attribute__((used)) static int etm4_get_next_comparator(struct etmv4_drvdata *drvdata, u32 type)
{
	int nr_comparator, index = 0;
	struct etmv4_config *config = &drvdata->config;

	/*
	 * nr_addr_cmp holds the number of comparator _pair_, so time 2
	 * for the total number of comparators.
	 */
	nr_comparator = drvdata->nr_addr_cmp * 2;

	/* Go through the tally of comparators looking for a free one. */
	while (index < nr_comparator) {
		switch (type) {
		case ETM_ADDR_TYPE_RANGE:
			if (config->addr_type[index] == ETM_ADDR_TYPE_NONE &&
			    config->addr_type[index + 1] == ETM_ADDR_TYPE_NONE)
				return index;

			/* Address range comparators go in pairs */
			index += 2;
			break;
		case ETM_ADDR_TYPE_START:
		case ETM_ADDR_TYPE_STOP:
			if (config->addr_type[index] == ETM_ADDR_TYPE_NONE)
				return index;

			/* Start/stop address can have odd indexes */
			index += 1;
			break;
		default:
			return -EINVAL;
		}
	}

	/* If we are here all the comparators have been used. */
	return -ENOSPC;
}