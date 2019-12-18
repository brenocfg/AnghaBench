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
struct qib_pportdata {struct qib_devdata* dd; } ;
struct qib_devdata {int (* f_get_ib_cfg ) (struct qib_pportdata*,int /*<<< orphan*/ ) ;} ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  QIB_IB_CFG_HRTBT ; 
 int scnprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 int stub1 (struct qib_pportdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t show_hrtbt_enb(struct qib_pportdata *ppd, char *buf)
{
	struct qib_devdata *dd = ppd->dd;
	int ret;

	ret = dd->f_get_ib_cfg(ppd, QIB_IB_CFG_HRTBT);
	ret = scnprintf(buf, PAGE_SIZE, "%d\n", ret);
	return ret;
}