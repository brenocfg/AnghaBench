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
typedef  int /*<<< orphan*/  u16 ;
struct qib_pportdata {struct qib_devdata* dd; } ;
struct qib_devdata {int (* f_set_ib_cfg ) (struct qib_pportdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  QIB_IB_CFG_HRTBT ; 
 int kstrtou16 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qib_dev_err (struct qib_devdata*,char*) ; 
 int stub1 (struct qib_pportdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t store_hrtbt_enb(struct qib_pportdata *ppd, const char *buf,
			       size_t count)
{
	struct qib_devdata *dd = ppd->dd;
	int ret;
	u16 val;

	ret = kstrtou16(buf, 0, &val);
	if (ret) {
		qib_dev_err(dd, "attempt to set invalid Heartbeat enable\n");
		return ret;
	}

	/*
	 * Set the "intentional" heartbeat enable per either of
	 * "Enable" and "Auto", as these are normally set together.
	 * This bit is consulted when leaving loopback mode,
	 * because entering loopback mode overrides it and automatically
	 * disables heartbeat.
	 */
	ret = dd->f_set_ib_cfg(ppd, QIB_IB_CFG_HRTBT, val);
	return ret < 0 ? ret : count;
}