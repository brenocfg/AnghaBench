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
typedef  int /*<<< orphan*/  u32 ;
struct work_struct {int dummy; } ;
struct asd_sas_phy {TYPE_2__* port; int /*<<< orphan*/  sas_prim_lock; int /*<<< orphan*/  sas_prim; } ;
struct asd_sas_event {struct asd_sas_phy* phy; } ;
struct TYPE_4__ {TYPE_1__* ha; } ;
struct TYPE_3__ {int /*<<< orphan*/  disco_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISCE_REVALIDATE_DOMAIN ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sas_discover_event (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct asd_sas_event* to_asd_sas_event (struct work_struct*) ; 

void sas_porte_broadcast_rcvd(struct work_struct *work)
{
	struct asd_sas_event *ev = to_asd_sas_event(work);
	struct asd_sas_phy *phy = ev->phy;
	unsigned long flags;
	u32 prim;

	spin_lock_irqsave(&phy->sas_prim_lock, flags);
	prim = phy->sas_prim;
	spin_unlock_irqrestore(&phy->sas_prim_lock, flags);

	pr_debug("broadcast received: %d\n", prim);
	sas_discover_event(phy->port, DISCE_REVALIDATE_DOMAIN);

	if (phy->port)
		flush_workqueue(phy->port->ha->disco_q);
}