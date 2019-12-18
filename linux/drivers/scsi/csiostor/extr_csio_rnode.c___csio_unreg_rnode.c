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
struct csio_rnode {int role; int /*<<< orphan*/  host_cmpl_q; } ;
struct csio_lnode {int /*<<< orphan*/  last_scan_ntgts; int /*<<< orphan*/  n_scsi_tgts; } ;
struct csio_hw {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int CSIO_RNFR_TARGET ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csio_dbg (struct csio_hw*,char*) ; 
 int /*<<< orphan*/  csio_hw_to_scsim (struct csio_hw*) ; 
 struct csio_hw* csio_lnode_to_hw (struct csio_lnode*) ; 
 struct csio_lnode* csio_rnode_to_lnode (struct csio_rnode*) ; 
 int /*<<< orphan*/  csio_scsi_cleanup_io_q (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  csio_unreg_rnode (struct csio_rnode*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_splice_tail_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tmp_q ; 

__attribute__((used)) static void
__csio_unreg_rnode(struct csio_rnode *rn)
{
	struct csio_lnode *ln = csio_rnode_to_lnode(rn);
	struct csio_hw *hw = csio_lnode_to_hw(ln);
	LIST_HEAD(tmp_q);
	int cmpl = 0;

	if (!list_empty(&rn->host_cmpl_q)) {
		csio_dbg(hw, "Returning completion queue I/Os\n");
		list_splice_tail_init(&rn->host_cmpl_q, &tmp_q);
		cmpl = 1;
	}

	if (rn->role & CSIO_RNFR_TARGET) {
		ln->n_scsi_tgts--;
		ln->last_scan_ntgts--;
	}

	spin_unlock_irq(&hw->lock);
	csio_unreg_rnode(rn);
	spin_lock_irq(&hw->lock);

	/* Cleanup I/Os that were waiting for rnode to unregister */
	if (cmpl)
		csio_scsi_cleanup_io_q(csio_hw_to_scsim(hw), &tmp_q);

}