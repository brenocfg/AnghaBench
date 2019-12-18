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
struct ibmpex_bmc_data {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 struct ibmpex_bmc_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  ibmpex_reset_high_low_data (struct ibmpex_bmc_data*) ; 

__attribute__((used)) static ssize_t ibmpex_high_low_store(struct device *dev,
				     struct device_attribute *devattr,
				     const char *buf, size_t count)
{
	struct ibmpex_bmc_data *data = dev_get_drvdata(dev);

	ibmpex_reset_high_low_data(data);

	return count;
}