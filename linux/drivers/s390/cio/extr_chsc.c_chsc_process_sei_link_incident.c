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
struct TYPE_2__ {int class; scalar_t__ null; } ;
struct lir {int /*<<< orphan*/  ic; TYPE_1__ iq; int /*<<< orphan*/  attached_node; int /*<<< orphan*/  incident_node; } ;
struct chsc_sei_nt0_area {int /*<<< orphan*/  rsid; int /*<<< orphan*/  rs; int /*<<< orphan*/ * ccdf; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIO_CRW_EVENT (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  LIR_IQ_CLASS_DEGRADED 129 
#define  LIR_IQ_CLASS_NOT_OPERATIONAL 128 
 int NODEID_LEN ; 
 int PARAMS_LEN ; 
 int /*<<< orphan*/  format_node_data (char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,char*,char*) ; 

__attribute__((used)) static void chsc_process_sei_link_incident(struct chsc_sei_nt0_area *sei_area)
{
	struct lir *lir = (struct lir *) &sei_area->ccdf;
	char iuparams[PARAMS_LEN], iunodeid[NODEID_LEN], auparams[PARAMS_LEN],
	     aunodeid[NODEID_LEN];

	CIO_CRW_EVENT(4, "chsc: link incident (rs=%02x, rs_id=%04x, iq=%02x)\n",
		      sei_area->rs, sei_area->rsid, sei_area->ccdf[0]);

	/* Ignore NULL Link Incident Records. */
	if (lir->iq.null)
		return;

	/* Inform user that a link requires maintenance actions because it has
	 * become degraded or not operational. Note that this log message is
	 * the primary intention behind a Link Incident Record. */

	format_node_data(iuparams, iunodeid, &lir->incident_node);
	format_node_data(auparams, aunodeid, &lir->attached_node);

	switch (lir->iq.class) {
	case LIR_IQ_CLASS_DEGRADED:
		pr_warn("Link degraded: RS=%02x RSID=%04x IC=%02x "
			"IUPARAMS=%s IUNODEID=%s AUPARAMS=%s AUNODEID=%s\n",
			sei_area->rs, sei_area->rsid, lir->ic, iuparams,
			iunodeid, auparams, aunodeid);
		break;
	case LIR_IQ_CLASS_NOT_OPERATIONAL:
		pr_err("Link stopped: RS=%02x RSID=%04x IC=%02x "
		       "IUPARAMS=%s IUNODEID=%s AUPARAMS=%s AUNODEID=%s\n",
		       sei_area->rs, sei_area->rsid, lir->ic, iuparams,
		       iunodeid, auparams, aunodeid);
		break;
	default:
		break;
	}
}