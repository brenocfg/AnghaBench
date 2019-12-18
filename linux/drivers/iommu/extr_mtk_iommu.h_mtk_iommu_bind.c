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
struct mtk_iommu_data {int /*<<< orphan*/  larb_imu; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int component_bind_all (struct device*,int /*<<< orphan*/ *) ; 
 struct mtk_iommu_data* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static inline int mtk_iommu_bind(struct device *dev)
{
	struct mtk_iommu_data *data = dev_get_drvdata(dev);

	return component_bind_all(dev, &data->larb_imu);
}