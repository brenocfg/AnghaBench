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
struct csio_lnode {int /*<<< orphan*/  nport_id; int /*<<< orphan*/  sm; TYPE_1__* fcfinfo; } ;
struct csio_hw {int /*<<< orphan*/  lock; } ;
typedef  enum csio_ln_ev { ____Placeholder_csio_ln_ev } csio_ln_ev ;
struct TYPE_2__ {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSIO_DB_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSIO_INC_STATS (struct csio_lnode*,int /*<<< orphan*/ ) ; 
#define  CSIO_LNE_CLOSE 132 
#define  CSIO_LNE_DOWN_LINK 131 
#define  CSIO_LNE_FAB_INIT_DONE 130 
#define  CSIO_LNE_LINK_DOWN 129 
#define  CSIO_LNE_LOGO 128 
 int /*<<< orphan*/  CSIO_LN_FC_LINKDOWN ; 
 int /*<<< orphan*/  CSIO_RNFE_CLOSE ; 
 int /*<<< orphan*/  CSIO_RNFE_DOWN ; 
 int /*<<< orphan*/  csio_is_phys_ln (struct csio_lnode*) ; 
 int /*<<< orphan*/  csio_ln_dbg (struct csio_lnode*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csio_lnode_async_event (struct csio_lnode*,int /*<<< orphan*/ ) ; 
 struct csio_hw* csio_lnode_to_hw (struct csio_lnode*) ; 
 int /*<<< orphan*/  csio_lns_offline ; 
 int /*<<< orphan*/  csio_lns_uninit ; 
 int /*<<< orphan*/  csio_post_event_rns (struct csio_lnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csio_set_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  n_evt_drop ; 
 int /*<<< orphan*/ * n_evt_sm ; 
 int /*<<< orphan*/  n_evt_unexp ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
csio_lns_ready(struct csio_lnode *ln, enum csio_ln_ev evt)
{
	struct csio_hw *hw = csio_lnode_to_hw(ln);

	CSIO_INC_STATS(ln, n_evt_sm[evt]);
	switch (evt) {
	case CSIO_LNE_FAB_INIT_DONE:
		csio_ln_dbg(ln,
			    "ignoring event %d recv from did x%x"
			    "in ln state[ready].\n", evt, ln->nport_id);
		CSIO_INC_STATS(ln, n_evt_drop);
		break;

	case CSIO_LNE_LINK_DOWN:
		csio_set_state(&ln->sm, csio_lns_offline);
		csio_post_event_rns(ln, CSIO_RNFE_DOWN);

		spin_unlock_irq(&hw->lock);
		csio_lnode_async_event(ln, CSIO_LN_FC_LINKDOWN);
		spin_lock_irq(&hw->lock);

		if (csio_is_phys_ln(ln)) {
			/* Remove FCF entry */
			list_del_init(&ln->fcfinfo->list);
		}
		break;

	case CSIO_LNE_DOWN_LINK:
		csio_set_state(&ln->sm, csio_lns_offline);
		csio_post_event_rns(ln, CSIO_RNFE_DOWN);

		/* Host need to issue aborts in case if FW has not returned
		 * WRs with status "ABORTED"
		 */
		spin_unlock_irq(&hw->lock);
		csio_lnode_async_event(ln, CSIO_LN_FC_LINKDOWN);
		spin_lock_irq(&hw->lock);

		if (csio_is_phys_ln(ln)) {
			/* Remove FCF entry */
			list_del_init(&ln->fcfinfo->list);
		}
		break;

	case CSIO_LNE_CLOSE:
		csio_set_state(&ln->sm, csio_lns_uninit);
		csio_post_event_rns(ln, CSIO_RNFE_CLOSE);
		break;

	case CSIO_LNE_LOGO:
		csio_set_state(&ln->sm, csio_lns_offline);
		csio_post_event_rns(ln, CSIO_RNFE_DOWN);
		break;

	default:
		csio_ln_dbg(ln,
			    "unexp ln event %d recv from did:x%x in "
			    "ln state[uninit].\n", evt, ln->nport_id);
		CSIO_INC_STATS(ln, n_evt_unexp);
		CSIO_DB_ASSERT(0);
		break;
	} /* switch event */
}