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
struct ib_mw {int /*<<< orphan*/  device; } ;
struct hns_roce_mw {int dummy; } ;
struct hns_roce_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hns_roce_mw_free (struct hns_roce_dev*,struct hns_roce_mw*) ; 
 int /*<<< orphan*/  kfree (struct hns_roce_mw*) ; 
 struct hns_roce_dev* to_hr_dev (int /*<<< orphan*/ ) ; 
 struct hns_roce_mw* to_hr_mw (struct ib_mw*) ; 

int hns_roce_dealloc_mw(struct ib_mw *ibmw)
{
	struct hns_roce_dev *hr_dev = to_hr_dev(ibmw->device);
	struct hns_roce_mw *mw = to_hr_mw(ibmw);

	hns_roce_mw_free(hr_dev, mw);
	kfree(mw);

	return 0;
}