#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct domain_device {int /*<<< orphan*/ * lldd_dev; TYPE_2__* port; } ;
struct TYPE_6__ {int /*<<< orphan*/  ddb_lock; } ;
struct asd_ha_struct {TYPE_3__ hw_prof; } ;
struct TYPE_5__ {TYPE_1__* ha; } ;
struct TYPE_4__ {struct asd_ha_struct* lldd_ha; } ;

/* Variables and functions */
 int /*<<< orphan*/  SISTER_DDB ; 
 int asd_ddbsite_read_word (struct asd_ha_struct*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asd_free_ddb (struct asd_ha_struct*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void asd_dev_gone(struct domain_device *dev)
{
	int ddb, sister_ddb;
	unsigned long flags;
	struct asd_ha_struct *asd_ha = dev->port->ha->lldd_ha;

	spin_lock_irqsave(&asd_ha->hw_prof.ddb_lock, flags);
	ddb = (int) (unsigned long) dev->lldd_dev;
	sister_ddb = asd_ddbsite_read_word(asd_ha, ddb, SISTER_DDB);

	if (sister_ddb != 0xFFFF)
		asd_free_ddb(asd_ha, sister_ddb);
	asd_free_ddb(asd_ha, ddb);
	dev->lldd_dev = NULL;
	spin_unlock_irqrestore(&asd_ha->hw_prof.ddb_lock, flags);
}