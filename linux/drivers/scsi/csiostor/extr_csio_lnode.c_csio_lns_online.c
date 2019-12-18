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
struct csio_lnode {int /*<<< orphan*/  nport_id; TYPE_1__* fcfinfo; int /*<<< orphan*/  sm; int /*<<< orphan*/  portid; } ;
struct csio_hw {int /*<<< orphan*/  lock; } ;
typedef  enum csio_ln_ev { ____Placeholder_csio_ln_ev } csio_ln_ev ;
struct TYPE_2__ {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSIO_INC_STATS (struct csio_lnode*,int /*<<< orphan*/ ) ; 
#define  CSIO_LNE_DOWN_LINK 131 
#define  CSIO_LNE_FAB_INIT_DONE 130 
#define  CSIO_LNE_LINKUP 129 
#define  CSIO_LNE_LINK_DOWN 128 
 int /*<<< orphan*/  CSIO_LN_FC_LINKUP ; 
 int /*<<< orphan*/  csio_is_phys_ln (struct csio_lnode*) ; 
 int /*<<< orphan*/  csio_ln_dbg (struct csio_lnode*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csio_ln_warn (struct csio_lnode*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csio_lnode_async_event (struct csio_lnode*,int /*<<< orphan*/ ) ; 
 struct csio_hw* csio_lnode_to_hw (struct csio_lnode*) ; 
 int /*<<< orphan*/  csio_lns_ready ; 
 int /*<<< orphan*/  csio_lns_uninit ; 
 int /*<<< orphan*/  csio_set_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  n_evt_drop ; 
 int /*<<< orphan*/ * n_evt_sm ; 
 int /*<<< orphan*/  n_evt_unexp ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
csio_lns_online(struct csio_lnode *ln, enum csio_ln_ev evt)
{
	struct csio_hw *hw = csio_lnode_to_hw(ln);

	CSIO_INC_STATS(ln, n_evt_sm[evt]);
	switch (evt) {
	case CSIO_LNE_LINKUP:
		csio_ln_warn(ln,
			     "warn: FCOE link is up already "
			     "Ignoring linkup on port:%d\n", ln->portid);
		CSIO_INC_STATS(ln, n_evt_drop);
		break;

	case CSIO_LNE_FAB_INIT_DONE:
		csio_set_state(&ln->sm, csio_lns_ready);

		spin_unlock_irq(&hw->lock);
		csio_lnode_async_event(ln, CSIO_LN_FC_LINKUP);
		spin_lock_irq(&hw->lock);

		break;

	case CSIO_LNE_LINK_DOWN:
		/* Fall through */
	case CSIO_LNE_DOWN_LINK:
		csio_set_state(&ln->sm, csio_lns_uninit);
		if (csio_is_phys_ln(ln)) {
			/* Remove FCF entry */
			list_del_init(&ln->fcfinfo->list);
		}
		break;

	default:
		csio_ln_dbg(ln,
			    "unexp ln event %d recv from did:x%x in "
			    "ln state[uninit].\n", evt, ln->nport_id);
		CSIO_INC_STATS(ln, n_evt_unexp);

		break;
	} /* switch event */
}