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
struct rproc_vring {int /*<<< orphan*/  vq; } ;
struct rproc {int /*<<< orphan*/  notifyids; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 struct rproc_vring* idr_find (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vring_interrupt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

irqreturn_t rproc_vq_interrupt(struct rproc *rproc, int notifyid)
{
	struct rproc_vring *rvring;

	dev_dbg(&rproc->dev, "vq index %d is interrupted\n", notifyid);

	rvring = idr_find(&rproc->notifyids, notifyid);
	if (!rvring || !rvring->vq)
		return IRQ_NONE;

	return vring_interrupt(0, rvring->vq);
}