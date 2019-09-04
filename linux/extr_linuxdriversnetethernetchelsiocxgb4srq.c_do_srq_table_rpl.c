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
struct srq_entry {int valid; unsigned int idx; void* max_msn; void* cur_msn; int /*<<< orphan*/  qbase; int /*<<< orphan*/  qlen; int /*<<< orphan*/  pdid; } ;
struct srq_data {int /*<<< orphan*/  comp; struct srq_entry* entryp; } ;
struct cpl_srq_table_rpl {scalar_t__ status; int /*<<< orphan*/  max_msn; int /*<<< orphan*/  cur_msn; int /*<<< orphan*/  qlen_qbase; int /*<<< orphan*/  rsvd_pdid; } ;
struct adapter {int /*<<< orphan*/  pdev_dev; struct srq_data* srq; } ;

/* Variables and functions */
 scalar_t__ CPL_CONTAINS_READ_RPL ; 
 int /*<<< orphan*/  GET_TID (struct cpl_srq_table_rpl const*) ; 
 int /*<<< orphan*/  SRQT_PDID_G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SRQT_QBASE_G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SRQT_QLEN_G (int /*<<< orphan*/ ) ; 
 unsigned int TID_TID_G (int /*<<< orphan*/ ) ; 
 void* be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__,unsigned int) ; 
 scalar_t__ unlikely (int) ; 

void do_srq_table_rpl(struct adapter *adap,
		      const struct cpl_srq_table_rpl *rpl)
{
	unsigned int idx = TID_TID_G(GET_TID(rpl));
	struct srq_data *s = adap->srq;
	struct srq_entry *e;

	if (unlikely(rpl->status != CPL_CONTAINS_READ_RPL)) {
		dev_err(adap->pdev_dev,
			"Unexpected SRQ_TABLE_RPL status %u for entry %u\n",
				rpl->status, idx);
		goto out;
	}

	/* Store the read entry */
	e = s->entryp;
	e->valid = 1;
	e->idx = idx;
	e->pdid = SRQT_PDID_G(be64_to_cpu(rpl->rsvd_pdid));
	e->qlen = SRQT_QLEN_G(be32_to_cpu(rpl->qlen_qbase));
	e->qbase = SRQT_QBASE_G(be32_to_cpu(rpl->qlen_qbase));
	e->cur_msn = be16_to_cpu(rpl->cur_msn);
	e->max_msn = be16_to_cpu(rpl->max_msn);
out:
	complete(&s->comp);
}