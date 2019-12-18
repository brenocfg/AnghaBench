#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct cxl {int psl_timebase_synced; TYPE_2__* native; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_4__ {TYPE_1__* sl_ops; } ;
struct TYPE_3__ {scalar_t__ (* timebase_read ) (struct cxl*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_FTR_HVMODE ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ abs (scalar_t__) ; 
 scalar_t__ cpu_has_feature (int /*<<< orphan*/ ) ; 
 scalar_t__ mftb () ; 
 int /*<<< orphan*/  pr_devel (char*,char*,int) ; 
 int /*<<< orphan*/  scnprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ stub1 (struct cxl*) ; 
 int tb_to_ns (scalar_t__) ; 
 struct cxl* to_cxl_adapter (struct device*) ; 

__attribute__((used)) static ssize_t psl_timebase_synced_show(struct device *device,
					struct device_attribute *attr,
					char *buf)
{
	struct cxl *adapter = to_cxl_adapter(device);
	u64 psl_tb, delta;

	/* Recompute the status only in native mode */
	if (cpu_has_feature(CPU_FTR_HVMODE)) {
		psl_tb = adapter->native->sl_ops->timebase_read(adapter);
		delta = abs(mftb() - psl_tb);

		/* CORE TB and PSL TB difference <= 16usecs ? */
		adapter->psl_timebase_synced = (tb_to_ns(delta) < 16000) ? true : false;
		pr_devel("PSL timebase %s - delta: 0x%016llx\n",
			 (tb_to_ns(delta) < 16000) ? "synchronized" :
			 "not synchronized", tb_to_ns(delta));
	}
	return scnprintf(buf, PAGE_SIZE, "%i\n", adapter->psl_timebase_synced);
}