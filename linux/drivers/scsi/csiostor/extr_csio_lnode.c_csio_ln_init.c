#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct csio_lnode {TYPE_1__* fcfinfo; int /*<<< orphan*/  fcf_lsthead; void* fcf_flowid; void* vnp_flowid; int /*<<< orphan*/  sm; } ;
struct csio_hw {int dummy; } ;
struct csio_fcf_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  kref; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSIO_INC_STATS (struct csio_hw*,int /*<<< orphan*/ ) ; 
 void* CSIO_INVALID_IDX ; 
 int EINVAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ csio_fdmi_enable ; 
 int /*<<< orphan*/  csio_init_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ csio_is_npiv_ln (struct csio_lnode*) ; 
 scalar_t__ csio_is_root_ln (struct csio_lnode*) ; 
 int /*<<< orphan*/  csio_ln_err (struct csio_lnode*,char*) ; 
 scalar_t__ csio_ln_fdmi_init (struct csio_lnode*) ; 
 struct csio_hw* csio_lnode_to_hw (struct csio_lnode*) ; 
 int /*<<< orphan*/  csio_lns_uninit ; 
 struct csio_lnode* csio_parent_lnode (struct csio_lnode*) ; 
 struct csio_lnode* csio_root_lnode (struct csio_lnode*) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  n_err_nomem ; 

__attribute__((used)) static int
csio_ln_init(struct csio_lnode *ln)
{
	int rv = -EINVAL;
	struct csio_lnode *rln, *pln;
	struct csio_hw *hw = csio_lnode_to_hw(ln);

	csio_init_state(&ln->sm, csio_lns_uninit);
	ln->vnp_flowid = CSIO_INVALID_IDX;
	ln->fcf_flowid = CSIO_INVALID_IDX;

	if (csio_is_root_ln(ln)) {

		/* This is the lnode used during initialization */

		ln->fcfinfo = kzalloc(sizeof(struct csio_fcf_info), GFP_KERNEL);
		if (!ln->fcfinfo) {
			csio_ln_err(ln, "Failed to alloc FCF record\n");
			CSIO_INC_STATS(hw, n_err_nomem);
			goto err;
		}

		INIT_LIST_HEAD(&ln->fcf_lsthead);
		kref_init(&ln->fcfinfo->kref);

		if (csio_fdmi_enable && csio_ln_fdmi_init(ln))
			goto err;

	} else { /* Either a non-root physical or a virtual lnode */

		/*
		 * THe rest is common for non-root physical and NPIV lnodes.
		 * Just get references to all other modules
		 */
		rln = csio_root_lnode(ln);

		if (csio_is_npiv_ln(ln)) {
			/* NPIV */
			pln = csio_parent_lnode(ln);
			kref_get(&pln->fcfinfo->kref);
			ln->fcfinfo = pln->fcfinfo;
		} else {
			/* Another non-root physical lnode (FCF) */
			ln->fcfinfo = kzalloc(sizeof(struct csio_fcf_info),
								GFP_KERNEL);
			if (!ln->fcfinfo) {
				csio_ln_err(ln, "Failed to alloc FCF info\n");
				CSIO_INC_STATS(hw, n_err_nomem);
				goto err;
			}

			kref_init(&ln->fcfinfo->kref);

			if (csio_fdmi_enable && csio_ln_fdmi_init(ln))
				goto err;
		}

	} /* if (!csio_is_root_ln(ln)) */

	return 0;
err:
	return rv;
}