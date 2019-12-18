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
typedef  int /*<<< orphan*/  u32 ;
struct hfi1_pportdata {struct hfi1_devdata* dd; } ;
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  QSFP_WAIT ; 
 int acquire_chip_resource (struct hfi1_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int qsfp_read (struct hfi1_pportdata*,int /*<<< orphan*/ ,int,void*,int) ; 
 int /*<<< orphan*/  qsfp_resource (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  release_chip_resource (struct hfi1_devdata*,int /*<<< orphan*/ ) ; 

int one_qsfp_read(struct hfi1_pportdata *ppd, u32 target, int addr, void *bp,
		  int len)
{
	struct hfi1_devdata *dd = ppd->dd;
	u32 resource = qsfp_resource(dd);
	int ret;

	ret = acquire_chip_resource(dd, resource, QSFP_WAIT);
	if (ret)
		return ret;
	ret = qsfp_read(ppd, target, addr, bp, len);
	release_chip_resource(dd, resource);

	return ret;
}