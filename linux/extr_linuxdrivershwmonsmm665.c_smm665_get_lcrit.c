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
struct smm665_data {int* critical_min_limit; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct smm665_data* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static int smm665_get_lcrit(struct device *dev, int index)
{
	struct smm665_data *data = dev_get_drvdata(dev);

	return data->critical_min_limit[index];
}