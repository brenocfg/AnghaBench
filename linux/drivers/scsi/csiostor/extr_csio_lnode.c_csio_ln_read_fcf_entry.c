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
struct csio_lnode {int /*<<< orphan*/  fcf_flowid; int /*<<< orphan*/  portid; struct csio_hw* hwp; } ;
struct csio_hw {int /*<<< orphan*/  mb_mempool; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSIO_INC_STATS (struct csio_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSIO_MB_DEFAULT_TMO ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  csio_err (struct csio_hw*,char*) ; 
 int /*<<< orphan*/  csio_fcoe_read_fcf_init_mb (struct csio_lnode*,struct csio_mb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void (*) (struct csio_hw*,struct csio_mb*)) ; 
 scalar_t__ csio_mb_issue (struct csio_hw*,struct csio_mb*) ; 
 struct csio_mb* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (struct csio_mb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  n_err_nomem ; 

__attribute__((used)) static int
csio_ln_read_fcf_entry(struct csio_lnode *ln,
			void (*cbfn) (struct csio_hw *, struct csio_mb *))
{
	struct csio_hw *hw = ln->hwp;
	struct csio_mb  *mbp;

	mbp = mempool_alloc(hw->mb_mempool, GFP_ATOMIC);
	if (!mbp) {
		CSIO_INC_STATS(hw, n_err_nomem);
		return -ENOMEM;
	}

	/* Get FCoE FCF information */
	csio_fcoe_read_fcf_init_mb(ln, mbp, CSIO_MB_DEFAULT_TMO,
				      ln->portid, ln->fcf_flowid, cbfn);

	if (csio_mb_issue(hw, mbp)) {
		csio_err(hw, "failed to issue FCOE FCF cmd\n");
		mempool_free(mbp, hw->mb_mempool);
		return -EINVAL;
	}

	return 0;
}