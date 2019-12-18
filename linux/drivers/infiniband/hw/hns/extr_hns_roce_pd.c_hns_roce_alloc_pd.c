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
typedef  int /*<<< orphan*/  uresp ;
struct ib_udata {int dummy; } ;
struct ib_pd {struct ib_device* device; } ;
struct ib_device {int dummy; } ;
struct hns_roce_pd {int /*<<< orphan*/  pdn; } ;
struct hns_roce_ib_alloc_pd_resp {int /*<<< orphan*/  pdn; } ;
struct hns_roce_dev {struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int hns_roce_pd_alloc (struct hns_roce_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hns_roce_pd_free (struct hns_roce_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ ib_copy_to_udata (struct ib_udata*,struct hns_roce_ib_alloc_pd_resp*,int) ; 
 struct hns_roce_dev* to_hr_dev (struct ib_device*) ; 
 struct hns_roce_pd* to_hr_pd (struct ib_pd*) ; 

int hns_roce_alloc_pd(struct ib_pd *ibpd, struct ib_udata *udata)
{
	struct ib_device *ib_dev = ibpd->device;
	struct hns_roce_dev *hr_dev = to_hr_dev(ib_dev);
	struct device *dev = hr_dev->dev;
	struct hns_roce_pd *pd = to_hr_pd(ibpd);
	int ret;

	ret = hns_roce_pd_alloc(to_hr_dev(ib_dev), &pd->pdn);
	if (ret) {
		dev_err(dev, "[alloc_pd]hns_roce_pd_alloc failed!\n");
		return ret;
	}

	if (udata) {
		struct hns_roce_ib_alloc_pd_resp uresp = {.pdn = pd->pdn};

		if (ib_copy_to_udata(udata, &uresp, sizeof(uresp))) {
			hns_roce_pd_free(to_hr_dev(ib_dev), pd->pdn);
			dev_err(dev, "[alloc_pd]ib_copy_to_udata failed!\n");
			return -EFAULT;
		}
	}

	return 0;
}