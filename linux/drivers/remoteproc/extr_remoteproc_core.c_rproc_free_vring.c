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
struct rproc_vring {TYPE_2__* rvdev; int /*<<< orphan*/  notifyid; } ;
struct rproc {scalar_t__ table_ptr; int /*<<< orphan*/  notifyids; } ;
struct fw_rsc_vdev {TYPE_1__* vring; } ;
struct TYPE_4__ {int rsc_offset; struct rproc_vring* vring; struct rproc* rproc; } ;
struct TYPE_3__ {int notifyid; scalar_t__ da; } ;

/* Variables and functions */
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void rproc_free_vring(struct rproc_vring *rvring)
{
	struct rproc *rproc = rvring->rvdev->rproc;
	int idx = rvring->rvdev->vring - rvring;
	struct fw_rsc_vdev *rsc;

	idr_remove(&rproc->notifyids, rvring->notifyid);

	/* reset resource entry info */
	rsc = (void *)rproc->table_ptr + rvring->rvdev->rsc_offset;
	rsc->vring[idx].da = 0;
	rsc->vring[idx].notifyid = -1;
}