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
struct csio_mb {int dummy; } ;
struct csio_iq_params {int fl0id; int fl1id; int /*<<< orphan*/  type; int /*<<< orphan*/  iqid; scalar_t__ vfn; int /*<<< orphan*/  pfn; } ;
struct csio_hw {int /*<<< orphan*/  mb_mempool; int /*<<< orphan*/  pfn; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSIO_MB_DEFAULT_TMO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FW_IQ_TYPE_FL_INT_CAP ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  csio_mb_iq_free (struct csio_hw*,struct csio_mb*,void*,int /*<<< orphan*/ ,struct csio_iq_params*,void (*) (struct csio_hw*,struct csio_mb*)) ; 
 int csio_mb_issue (struct csio_hw*,struct csio_mb*) ; 
 int csio_q_flid (struct csio_hw*,int) ; 
 int csio_q_iq_flq_idx (struct csio_hw*,int) ; 
 int /*<<< orphan*/  csio_q_iqid (struct csio_hw*,int) ; 
 int csio_wr_iq_destroy_rsp (struct csio_hw*,struct csio_mb*,int) ; 
 struct csio_mb* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (struct csio_mb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct csio_iq_params*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
csio_wr_iq_destroy(struct csio_hw *hw, void *priv, int iq_idx,
		   void (*cbfn)(struct csio_hw *, struct csio_mb *))
{
	int rv = 0;
	struct csio_mb  *mbp;
	struct csio_iq_params iqp;
	int flq_idx;

	memset(&iqp, 0, sizeof(struct csio_iq_params));

	mbp = mempool_alloc(hw->mb_mempool, GFP_ATOMIC);
	if (!mbp)
		return -ENOMEM;

	iqp.pfn		= hw->pfn;
	iqp.vfn		= 0;
	iqp.iqid	= csio_q_iqid(hw, iq_idx);
	iqp.type	= FW_IQ_TYPE_FL_INT_CAP;

	flq_idx = csio_q_iq_flq_idx(hw, iq_idx);
	if (flq_idx != -1)
		iqp.fl0id = csio_q_flid(hw, flq_idx);
	else
		iqp.fl0id = 0xFFFF;

	iqp.fl1id = 0xFFFF;

	csio_mb_iq_free(hw, mbp, priv, CSIO_MB_DEFAULT_TMO, &iqp, cbfn);

	rv = csio_mb_issue(hw, mbp);
	if (rv != 0) {
		mempool_free(mbp, hw->mb_mempool);
		return rv;
	}

	if (cbfn != NULL)
		return 0;

	return csio_wr_iq_destroy_rsp(hw, mbp, iq_idx);
}