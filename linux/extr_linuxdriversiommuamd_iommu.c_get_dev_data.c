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
struct iommu_dev_data {int dummy; } ;
struct TYPE_2__ {struct iommu_dev_data* iommu; } ;
struct device {TYPE_1__ archdata; } ;

/* Variables and functions */

struct iommu_dev_data *get_dev_data(struct device *dev)
{
	return dev->archdata.iommu;
}