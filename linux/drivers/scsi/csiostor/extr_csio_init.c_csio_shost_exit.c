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
struct csio_lnode {int dummy; } ;
struct csio_hw {int /*<<< orphan*/  lock; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  csio_evtq_flush (struct csio_hw*) ; 
 struct Scsi_Host* csio_ln_to_shost (struct csio_lnode*) ; 
 int /*<<< orphan*/  csio_lnode_exit (struct csio_lnode*) ; 
 struct csio_hw* csio_lnode_to_hw (struct csio_lnode*) ; 
 int /*<<< orphan*/  fc_remove_host (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_remove_host (struct Scsi_Host*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void
csio_shost_exit(struct csio_lnode *ln)
{
	struct Scsi_Host *shost = csio_ln_to_shost(ln);
	struct csio_hw *hw = csio_lnode_to_hw(ln);

	/* Inform transport */
	fc_remove_host(shost);

	/* Inform SCSI ML */
	scsi_remove_host(shost);

	/* Flush all the events, so that any rnode removal events
	 * already queued are all handled, before we remove the lnode.
	 */
	spin_lock_irq(&hw->lock);
	csio_evtq_flush(hw);
	spin_unlock_irq(&hw->lock);

	csio_lnode_exit(ln);
	scsi_host_put(shost);
}