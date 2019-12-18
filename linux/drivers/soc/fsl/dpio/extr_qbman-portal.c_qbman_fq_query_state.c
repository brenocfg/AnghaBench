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
typedef  int u32 ;
struct qbman_swp {int dummy; } ;
struct qbman_fq_query_np_rslt {int verb; int /*<<< orphan*/  rslt; } ;
struct qbman_fq_query_desc {int /*<<< orphan*/  fqid; } ;

/* Variables and functions */
 int EBUSY ; 
 int EIO ; 
 int QBMAN_FQ_QUERY_NP ; 
 int /*<<< orphan*/  QBMAN_MC_RSLT_OK ; 
 int QBMAN_RESPONSE_VERB_MASK ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  pr_err (char*,int,...) ; 
 void* qbman_swp_mc_complete (struct qbman_swp*,struct qbman_fq_query_desc*,int) ; 
 scalar_t__ qbman_swp_mc_start (struct qbman_swp*) ; 

int qbman_fq_query_state(struct qbman_swp *s, u32 fqid,
			 struct qbman_fq_query_np_rslt *r)
{
	struct qbman_fq_query_desc *p;
	void *resp;

	p = (struct qbman_fq_query_desc *)qbman_swp_mc_start(s);
	if (!p)
		return -EBUSY;

	/* FQID is a 24 bit value */
	p->fqid = cpu_to_le32(fqid & 0x00FFFFFF);
	resp = qbman_swp_mc_complete(s, p, QBMAN_FQ_QUERY_NP);
	if (!resp) {
		pr_err("qbman: Query FQID %d NP fields failed, no response\n",
		       fqid);
		return -EIO;
	}
	*r = *(struct qbman_fq_query_np_rslt *)resp;
	/* Decode the outcome */
	WARN_ON((r->verb & QBMAN_RESPONSE_VERB_MASK) != QBMAN_FQ_QUERY_NP);

	/* Determine success or failure */
	if (r->rslt != QBMAN_MC_RSLT_OK) {
		pr_err("Query NP fields of FQID 0x%x failed, code=0x%02x\n",
		       p->fqid, r->rslt);
		return -EIO;
	}

	return 0;
}