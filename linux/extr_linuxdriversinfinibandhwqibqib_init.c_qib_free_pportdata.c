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
struct TYPE_3__ {int /*<<< orphan*/ * rc_delayed_comp; int /*<<< orphan*/ * rc_qacks; int /*<<< orphan*/ * rc_acks; } ;
struct TYPE_4__ {int /*<<< orphan*/ * pmastats; TYPE_1__ rvp; } ;
struct qib_pportdata {TYPE_2__ ibport_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qib_free_pportdata(struct qib_pportdata *ppd)
{
	free_percpu(ppd->ibport_data.pmastats);
	free_percpu(ppd->ibport_data.rvp.rc_acks);
	free_percpu(ppd->ibport_data.rvp.rc_qacks);
	free_percpu(ppd->ibport_data.rvp.rc_delayed_comp);
	ppd->ibport_data.pmastats = NULL;
}