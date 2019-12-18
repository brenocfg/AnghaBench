#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {int dummy; } ;
struct TYPE_3__ {int req_depth; int /*<<< orphan*/  scsi_lookup_lock; struct scsi_cmnd** ScsiLookup; } ;
typedef  TYPE_1__ MPT_ADAPTER ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int
SCPNT_TO_LOOKUP_IDX(MPT_ADAPTER *ioc, struct scsi_cmnd *sc)
{
	unsigned long	flags;
	int i, index=-1;

	spin_lock_irqsave(&ioc->scsi_lookup_lock, flags);
	for (i = 0; i < ioc->req_depth; i++) {
		if (ioc->ScsiLookup[i] == sc) {
			index = i;
			goto out;
		}
	}

 out:
	spin_unlock_irqrestore(&ioc->scsi_lookup_lock, flags);
	return index;
}