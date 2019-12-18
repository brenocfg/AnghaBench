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
struct TYPE_3__ {int /*<<< orphan*/  flid; } ;
struct TYPE_4__ {TYPE_1__ fl; } ;
struct csio_q {int inc_idx; TYPE_2__ un; } ;
struct csio_hw {int dummy; } ;

/* Variables and functions */
 int DBPRIO_F ; 
 int DBTYPE_F ; 
 int /*<<< orphan*/  MYPF_REG (int /*<<< orphan*/ ) ; 
 int PIDX_T5_V (int) ; 
 int QID_V (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SGE_PF_KDOORBELL_A ; 
 int /*<<< orphan*/  csio_wr_reg32 (struct csio_hw*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
csio_wr_ring_fldb(struct csio_hw *hw, struct csio_q *flq)
{
	/*
	 * Ring the doorbell only when we have atleast CSIO_QCREDIT_SZ
	 * number of bytes in the freelist queue. This translates to atleast
	 * 8 freelist buffer pointers (since each pointer is 8 bytes).
	 */
	if (flq->inc_idx >= 8) {
		csio_wr_reg32(hw, DBPRIO_F | QID_V(flq->un.fl.flid) |
				  PIDX_T5_V(flq->inc_idx / 8) | DBTYPE_F,
				  MYPF_REG(SGE_PF_KDOORBELL_A));
		flq->inc_idx &= 7;
	}
}