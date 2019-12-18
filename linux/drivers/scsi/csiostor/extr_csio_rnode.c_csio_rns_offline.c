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
struct csio_rnode {int /*<<< orphan*/  nport_id; int /*<<< orphan*/  sm; int /*<<< orphan*/  rdev_entry; } ;
struct csio_lnode {int dummy; } ;
typedef  enum csio_rn_ev { ____Placeholder_csio_rn_ev } csio_rn_ev ;

/* Variables and functions */
 int /*<<< orphan*/  CSIO_INC_STATS (struct csio_rnode*,int /*<<< orphan*/ ) ; 
#define  CSIO_RNFE_CLOSE 132 
#define  CSIO_RNFE_DOWN 131 
#define  CSIO_RNFE_LOGGED_IN 130 
#define  CSIO_RNFE_NAME_MISSING 129 
#define  CSIO_RNFE_PLOGI_RECV 128 
 int /*<<< orphan*/  __csio_reg_rnode (struct csio_rnode*) ; 
 int /*<<< orphan*/  csio_ln_dbg (struct csio_lnode*,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csio_post_event (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  csio_rn_flowid (struct csio_rnode*) ; 
 int csio_rn_verify_rparams (struct csio_lnode*,struct csio_rnode*,int /*<<< orphan*/ ) ; 
 struct csio_lnode* csio_rnode_to_lnode (struct csio_rnode*) ; 
 int /*<<< orphan*/  csio_rns_disappeared ; 
 int /*<<< orphan*/  csio_rns_ready ; 
 int /*<<< orphan*/  csio_rns_uninit ; 
 int /*<<< orphan*/  csio_set_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  n_err_inval ; 
 int /*<<< orphan*/  n_evt_drop ; 
 int /*<<< orphan*/ * n_evt_sm ; 
 int /*<<< orphan*/  n_evt_unexp ; 

__attribute__((used)) static void
csio_rns_offline(struct csio_rnode *rn, enum csio_rn_ev evt)
{
	struct csio_lnode *ln = csio_rnode_to_lnode(rn);
	int ret = 0;

	CSIO_INC_STATS(rn, n_evt_sm[evt]);

	switch (evt) {
	case CSIO_RNFE_LOGGED_IN:
	case CSIO_RNFE_PLOGI_RECV:
		ret = csio_rn_verify_rparams(ln, rn, rn->rdev_entry);
		if (!ret) {
			csio_set_state(&rn->sm, csio_rns_ready);
			__csio_reg_rnode(rn);
		} else {
			CSIO_INC_STATS(rn, n_err_inval);
			csio_post_event(&rn->sm, CSIO_RNFE_CLOSE);
		}
		break;

	case CSIO_RNFE_DOWN:
		csio_ln_dbg(ln,
			"ssni:x%x Ignoring event %d recv from did:x%x "
			"in rn state[offline]\n", csio_rn_flowid(rn), evt,
			rn->nport_id);
		CSIO_INC_STATS(rn, n_evt_drop);
		break;

	case CSIO_RNFE_CLOSE:
		/* Each rnode receives CLOSE event when driver is removed or
		 * device is reset
		 * Note: All outstanding IOs on remote port need to returned
		 * to uppper layer with appropriate error before sending
		 * CLOSE event
		 */
		csio_set_state(&rn->sm, csio_rns_uninit);
		break;

	case CSIO_RNFE_NAME_MISSING:
		csio_set_state(&rn->sm, csio_rns_disappeared);
		break;

	default:
		csio_ln_dbg(ln,
			"ssni:x%x unexp event %d recv from did:x%x "
			"in rn state[offline]\n", csio_rn_flowid(rn), evt,
			rn->nport_id);
		CSIO_INC_STATS(rn, n_evt_unexp);
		break;
	}
}