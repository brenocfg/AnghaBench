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
struct csio_rnode {int role; scalar_t__ nport_id; } ;
struct csio_lnode {int /*<<< orphan*/  n_scsi_tgts; } ;
struct csio_hw {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int CSIO_RNFR_TARGET ; 
 scalar_t__ FC_FID_MGMT_SERV ; 
 int /*<<< orphan*/  csio_ln_fdmi_start (struct csio_lnode*,void*) ; 
 struct csio_hw* csio_lnode_to_hw (struct csio_lnode*) ; 
 int /*<<< orphan*/  csio_reg_rnode (struct csio_rnode*) ; 
 struct csio_lnode* csio_rnode_to_lnode (struct csio_rnode*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
__csio_reg_rnode(struct csio_rnode *rn)
{
	struct csio_lnode *ln = csio_rnode_to_lnode(rn);
	struct csio_hw *hw = csio_lnode_to_hw(ln);

	spin_unlock_irq(&hw->lock);
	csio_reg_rnode(rn);
	spin_lock_irq(&hw->lock);

	if (rn->role & CSIO_RNFR_TARGET)
		ln->n_scsi_tgts++;

	if (rn->nport_id == FC_FID_MGMT_SERV)
		csio_ln_fdmi_start(ln, (void *) rn);
}