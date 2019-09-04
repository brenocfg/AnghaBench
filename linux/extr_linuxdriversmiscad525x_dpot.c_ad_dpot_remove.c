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
struct dpot_data {int wipers; int /*<<< orphan*/  feat; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int DPOT_RDAC0 ; 
 int MAX_RDACS ; 
 int /*<<< orphan*/  ad_dpot_remove_files (struct device*,int /*<<< orphan*/ ,int) ; 
 struct dpot_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  kfree (struct dpot_data*) ; 

int ad_dpot_remove(struct device *dev)
{
	struct dpot_data *data = dev_get_drvdata(dev);
	int i;

	for (i = DPOT_RDAC0; i < MAX_RDACS; i++)
		if (data->wipers & (1 << i))
			ad_dpot_remove_files(dev, data->feat, i);

	kfree(data);

	return 0;
}