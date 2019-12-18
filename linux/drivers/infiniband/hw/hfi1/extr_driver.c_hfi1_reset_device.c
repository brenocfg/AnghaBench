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
struct hfi1_pportdata {int dummy; } ;
struct hfi1_devdata {int flags; int num_pports; struct hfi1_pportdata* pport; scalar_t__ rcd; int /*<<< orphan*/  kregbase1; } ;
struct TYPE_2__ {scalar_t__ sps_ctxts; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int ENXIO ; 
 int HFI1_HAS_SEND_DMA ; 
 int HFI1_PRESENT ; 
 int /*<<< orphan*/  dd_dev_err (struct hfi1_devdata*,char*,int,int) ; 
 int /*<<< orphan*/  dd_dev_info (struct hfi1_devdata*,char*,int) ; 
 int hfi1_init (struct hfi1_devdata*,int) ; 
 struct hfi1_devdata* hfi1_lookup (int) ; 
 int /*<<< orphan*/  hfi1_mutex ; 
 int /*<<< orphan*/  hfi1_reset_cpu_counters (struct hfi1_devdata*) ; 
 TYPE_1__ hfi1_stats ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdma_exit (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  shutdown_led_override (struct hfi1_pportdata*) ; 

int hfi1_reset_device(int unit)
{
	int ret;
	struct hfi1_devdata *dd = hfi1_lookup(unit);
	struct hfi1_pportdata *ppd;
	int pidx;

	if (!dd) {
		ret = -ENODEV;
		goto bail;
	}

	dd_dev_info(dd, "Reset on unit %u requested\n", unit);

	if (!dd->kregbase1 || !(dd->flags & HFI1_PRESENT)) {
		dd_dev_info(dd,
			    "Invalid unit number %u or not initialized or not present\n",
			    unit);
		ret = -ENXIO;
		goto bail;
	}

	/* If there are any user/vnic contexts, we cannot reset */
	mutex_lock(&hfi1_mutex);
	if (dd->rcd)
		if (hfi1_stats.sps_ctxts) {
			mutex_unlock(&hfi1_mutex);
			ret = -EBUSY;
			goto bail;
		}
	mutex_unlock(&hfi1_mutex);

	for (pidx = 0; pidx < dd->num_pports; ++pidx) {
		ppd = dd->pport + pidx;

		shutdown_led_override(ppd);
	}
	if (dd->flags & HFI1_HAS_SEND_DMA)
		sdma_exit(dd);

	hfi1_reset_cpu_counters(dd);

	ret = hfi1_init(dd, 1);

	if (ret)
		dd_dev_err(dd,
			   "Reinitialize unit %u after reset failed with %d\n",
			   unit, ret);
	else
		dd_dev_info(dd, "Reinitialized unit %u after resetting\n",
			    unit);

bail:
	return ret;
}