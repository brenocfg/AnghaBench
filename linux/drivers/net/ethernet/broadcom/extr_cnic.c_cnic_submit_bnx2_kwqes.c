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
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct kwqe {int dummy; } ;
struct cnic_local {scalar_t__ kwq_prod_idx; int /*<<< orphan*/  cnic_ulp_lock; int /*<<< orphan*/  kwq_io_addr; struct kwqe** kwq; int /*<<< orphan*/  cnic_local_flags; } ;
struct cnic_dev {int /*<<< orphan*/  flags; struct cnic_local* cnic_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  CNIC_F_CNIC_UP ; 
 int /*<<< orphan*/  CNIC_LCL_FL_KWQ_INIT ; 
 int /*<<< orphan*/  CNIC_WR16 (struct cnic_dev*,int /*<<< orphan*/ ,scalar_t__) ; 
 int EAGAIN ; 
 size_t KWQ_IDX (scalar_t__) ; 
 size_t KWQ_PG (scalar_t__) ; 
 scalar_t__ MAX_KWQ_IDX ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ cnic_kwq_avail (struct cnic_local*) ; 
 int /*<<< orphan*/  memcpy (struct kwqe*,struct kwqe*,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cnic_submit_bnx2_kwqes(struct cnic_dev *dev, struct kwqe *wqes[],
				  u32 num_wqes)
{
	struct cnic_local *cp = dev->cnic_priv;
	struct kwqe *prod_qe;
	u16 prod, sw_prod, i;

	if (!test_bit(CNIC_F_CNIC_UP, &dev->flags))
		return -EAGAIN;		/* bnx2 is down */

	spin_lock_bh(&cp->cnic_ulp_lock);
	if (num_wqes > cnic_kwq_avail(cp) &&
	    !test_bit(CNIC_LCL_FL_KWQ_INIT, &cp->cnic_local_flags)) {
		spin_unlock_bh(&cp->cnic_ulp_lock);
		return -EAGAIN;
	}

	clear_bit(CNIC_LCL_FL_KWQ_INIT, &cp->cnic_local_flags);

	prod = cp->kwq_prod_idx;
	sw_prod = prod & MAX_KWQ_IDX;
	for (i = 0; i < num_wqes; i++) {
		prod_qe = &cp->kwq[KWQ_PG(sw_prod)][KWQ_IDX(sw_prod)];
		memcpy(prod_qe, wqes[i], sizeof(struct kwqe));
		prod++;
		sw_prod = prod & MAX_KWQ_IDX;
	}
	cp->kwq_prod_idx = prod;

	CNIC_WR16(dev, cp->kwq_io_addr, cp->kwq_prod_idx);

	spin_unlock_bh(&cp->cnic_ulp_lock);
	return 0;
}