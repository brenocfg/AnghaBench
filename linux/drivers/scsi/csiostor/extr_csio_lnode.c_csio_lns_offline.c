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
struct csio_lnode {int /*<<< orphan*/  nport_id; int /*<<< orphan*/  sm; int /*<<< orphan*/  fcf_lsthead; TYPE_1__* fcfinfo; } ;
struct csio_hw {struct csio_lnode* rln; } ;
typedef  enum csio_ln_ev { ____Placeholder_csio_ln_ev } csio_ln_ev ;
struct TYPE_2__ {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSIO_DB_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSIO_INC_STATS (struct csio_lnode*,int /*<<< orphan*/ ) ; 
#define  CSIO_LNE_CLOSE 132 
#define  CSIO_LNE_DOWN_LINK 131 
#define  CSIO_LNE_LINKUP 130 
#define  CSIO_LNE_LINK_DOWN 129 
#define  CSIO_LNE_LOGO 128 
 int /*<<< orphan*/  CSIO_RNFE_CLOSE ; 
 int /*<<< orphan*/  csio_is_phys_ln (struct csio_lnode*) ; 
 int /*<<< orphan*/  csio_ln_dbg (struct csio_lnode*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csio_ln_read_fcf_cbfn ; 
 int csio_ln_read_fcf_entry (struct csio_lnode*,int /*<<< orphan*/ ) ; 
 int csio_ln_vnp_read (struct csio_lnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csio_ln_vnp_read_cbfn ; 
 struct csio_hw* csio_lnode_to_hw (struct csio_lnode*) ; 
 int /*<<< orphan*/  csio_lns_online ; 
 int /*<<< orphan*/  csio_lns_uninit ; 
 int /*<<< orphan*/  csio_post_event_rns (struct csio_lnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csio_set_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  n_err ; 
 int /*<<< orphan*/  n_evt_drop ; 
 int /*<<< orphan*/ * n_evt_sm ; 
 int /*<<< orphan*/  n_evt_unexp ; 

__attribute__((used)) static void
csio_lns_offline(struct csio_lnode *ln, enum csio_ln_ev evt)
{
	struct csio_hw *hw = csio_lnode_to_hw(ln);
	struct csio_lnode *rln = hw->rln;
	int rv;

	CSIO_INC_STATS(ln, n_evt_sm[evt]);
	switch (evt) {
	case CSIO_LNE_LINKUP:
		csio_set_state(&ln->sm, csio_lns_online);
		/* Read FCF only for physical lnode */
		if (csio_is_phys_ln(ln)) {
			rv = csio_ln_read_fcf_entry(ln,
					csio_ln_read_fcf_cbfn);
			if (rv != 0) {
				/* TODO: Send HW RESET event */
				CSIO_INC_STATS(ln, n_err);
				break;
			}

			/* Add FCF record */
			list_add_tail(&ln->fcfinfo->list, &rln->fcf_lsthead);
		}

		rv = csio_ln_vnp_read(ln, csio_ln_vnp_read_cbfn);
		if (rv != 0) {
			/* TODO: Send HW RESET event */
			CSIO_INC_STATS(ln, n_err);
		}
		break;

	case CSIO_LNE_LINK_DOWN:
	case CSIO_LNE_DOWN_LINK:
	case CSIO_LNE_LOGO:
		csio_ln_dbg(ln,
			    "ignoring event %d recv from did x%x"
			    "in ln state[offline].\n", evt, ln->nport_id);
		CSIO_INC_STATS(ln, n_evt_drop);
		break;

	case CSIO_LNE_CLOSE:
		csio_set_state(&ln->sm, csio_lns_uninit);
		csio_post_event_rns(ln, CSIO_RNFE_CLOSE);
		break;

	default:
		csio_ln_dbg(ln,
			    "unexp ln event %d recv from did:x%x in "
			    "ln state[offline]\n", evt, ln->nport_id);
		CSIO_INC_STATS(ln, n_evt_unexp);
		CSIO_DB_ASSERT(0);
		break;
	} /* switch event */
}