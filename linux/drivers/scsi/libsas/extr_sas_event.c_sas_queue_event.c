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
struct sas_work {int dummy; } ;
struct sas_ha_struct {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int sas_queue_work (struct sas_ha_struct*,struct sas_work*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int sas_queue_event(int event, struct sas_work *work,
			    struct sas_ha_struct *ha)
{
	unsigned long flags;
	int rc;

	spin_lock_irqsave(&ha->lock, flags);
	rc = sas_queue_work(ha, work);
	spin_unlock_irqrestore(&ha->lock, flags);

	return rc;
}