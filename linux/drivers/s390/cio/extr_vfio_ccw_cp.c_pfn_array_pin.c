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
struct pfn_array {int pa_nr; int /*<<< orphan*/  pa_iova_pfn; int /*<<< orphan*/  pa_pfn; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int IOMMU_READ ; 
 int IOMMU_WRITE ; 
 int vfio_pin_pages (struct device*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfio_unpin_pages (struct device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pfn_array_pin(struct pfn_array *pa, struct device *mdev)
{
	int ret = 0;

	ret = vfio_pin_pages(mdev, pa->pa_iova_pfn, pa->pa_nr,
			     IOMMU_READ | IOMMU_WRITE, pa->pa_pfn);

	if (ret < 0) {
		goto err_out;
	} else if (ret > 0 && ret != pa->pa_nr) {
		vfio_unpin_pages(mdev, pa->pa_iova_pfn, ret);
		ret = -EINVAL;
		goto err_out;
	}

	return ret;

err_out:
	pa->pa_nr = 0;

	return ret;
}