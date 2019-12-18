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
struct fc_fcp_pkt {int state; int /*<<< orphan*/  scsi_pkt_lock; } ;

/* Variables and functions */
 int EPERM ; 
 int FC_SRB_COMPL ; 
 int /*<<< orphan*/  fc_fcp_pkt_hold (struct fc_fcp_pkt*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int fc_fcp_lock_pkt(struct fc_fcp_pkt *fsp)
{
	spin_lock_bh(&fsp->scsi_pkt_lock);
	if (fsp->state & FC_SRB_COMPL) {
		spin_unlock_bh(&fsp->scsi_pkt_lock);
		return -EPERM;
	}

	fc_fcp_pkt_hold(fsp);
	return 0;
}