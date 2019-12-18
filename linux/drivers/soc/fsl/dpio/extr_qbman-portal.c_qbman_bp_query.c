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
typedef  int /*<<< orphan*/  u16 ;
struct qbman_swp {int dummy; } ;
struct qbman_bp_query_rslt {int verb; scalar_t__ rslt; } ;
struct qbman_bp_query_desc {int /*<<< orphan*/  bpid; } ;

/* Variables and functions */
 int EBUSY ; 
 int EIO ; 
 int QBMAN_BP_QUERY ; 
 scalar_t__ QBMAN_MC_RSLT_OK ; 
 int QBMAN_RESPONSE_VERB_MASK ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,...) ; 
 void* qbman_swp_mc_complete (struct qbman_swp*,struct qbman_bp_query_desc*,int) ; 
 scalar_t__ qbman_swp_mc_start (struct qbman_swp*) ; 

int qbman_bp_query(struct qbman_swp *s, u16 bpid,
		   struct qbman_bp_query_rslt *r)
{
	struct qbman_bp_query_desc *p;
	void *resp;

	p = (struct qbman_bp_query_desc *)qbman_swp_mc_start(s);
	if (!p)
		return -EBUSY;

	p->bpid = cpu_to_le16(bpid);
	resp = qbman_swp_mc_complete(s, p, QBMAN_BP_QUERY);
	if (!resp) {
		pr_err("qbman: Query BPID %d fields failed, no response\n",
		       bpid);
		return -EIO;
	}
	*r = *(struct qbman_bp_query_rslt *)resp;
	/* Decode the outcome */
	WARN_ON((r->verb & QBMAN_RESPONSE_VERB_MASK) != QBMAN_BP_QUERY);

	/* Determine success or failure */
	if (r->rslt != QBMAN_MC_RSLT_OK) {
		pr_err("Query fields of BPID 0x%x failed, code=0x%02x\n",
		       bpid, r->rslt);
		return -EIO;
	}

	return 0;
}