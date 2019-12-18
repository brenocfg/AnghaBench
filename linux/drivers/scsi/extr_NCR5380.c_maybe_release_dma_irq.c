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
struct Scsi_Host {int dummy; } ;
struct NCR5380_hostdata {int /*<<< orphan*/  selecting; int /*<<< orphan*/  connected; int /*<<< orphan*/  autosense; int /*<<< orphan*/  unissued; int /*<<< orphan*/  disconnected; } ;

/* Variables and functions */
 int /*<<< orphan*/  NCR5380_release_dma_irq (struct Scsi_Host*) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 struct NCR5380_hostdata* shost_priv (struct Scsi_Host*) ; 

__attribute__((used)) static inline void maybe_release_dma_irq(struct Scsi_Host *instance)
{
	struct NCR5380_hostdata *hostdata = shost_priv(instance);

	/* Caller does the locking needed to set & test these data atomically */
	if (list_empty(&hostdata->disconnected) &&
	    list_empty(&hostdata->unissued) &&
	    list_empty(&hostdata->autosense) &&
	    !hostdata->connected &&
	    !hostdata->selecting) {
		NCR5380_release_dma_irq(instance);
	}
}