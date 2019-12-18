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
typedef  scalar_t__ u32 ;
struct hfi1_devdata {int dummy; } ;
struct TYPE_2__ {scalar_t__ alloced; } ;
struct hfi1_ctxtdata {scalar_t__ eager_base; scalar_t__ expected_base; scalar_t__ expected_count; TYPE_1__ egrbufs; struct hfi1_devdata* dd; } ;

/* Variables and functions */
 int /*<<< orphan*/  PT_INVALID ; 
 int /*<<< orphan*/  hfi1_put_tid (struct hfi1_devdata*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void hfi1_clear_tids(struct hfi1_ctxtdata *rcd)
{
	struct hfi1_devdata *dd = rcd->dd;
	u32 i;

	/* this could be optimized */
	for (i = rcd->eager_base; i < rcd->eager_base +
		     rcd->egrbufs.alloced; i++)
		hfi1_put_tid(dd, i, PT_INVALID, 0, 0);

	for (i = rcd->expected_base;
			i < rcd->expected_base + rcd->expected_count; i++)
		hfi1_put_tid(dd, i, PT_INVALID, 0, 0);
}