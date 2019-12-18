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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct qbman_swp {int dummy; } ;
struct qbman_acquire_rslt {int verb; scalar_t__ rslt; unsigned int num; int /*<<< orphan*/ * buf; } ;
struct qbman_acquire_desc {unsigned int num; int /*<<< orphan*/  bpid; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int EIO ; 
 int QBMAN_MC_ACQUIRE ; 
 scalar_t__ QBMAN_MC_RSLT_OK ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,...) ; 
 struct qbman_acquire_rslt* qbman_swp_mc_complete (struct qbman_swp*,struct qbman_acquire_desc*,int) ; 
 struct qbman_acquire_desc* qbman_swp_mc_start (struct qbman_swp*) ; 
 scalar_t__ unlikely (int) ; 

int qbman_swp_acquire(struct qbman_swp *s, u16 bpid, u64 *buffers,
		      unsigned int num_buffers)
{
	struct qbman_acquire_desc *p;
	struct qbman_acquire_rslt *r;
	int i;

	if (!num_buffers || (num_buffers > 7))
		return -EINVAL;

	/* Start the management command */
	p = qbman_swp_mc_start(s);

	if (!p)
		return -EBUSY;

	/* Encode the caller-provided attributes */
	p->bpid = cpu_to_le16(bpid);
	p->num = num_buffers;

	/* Complete the management command */
	r = qbman_swp_mc_complete(s, p, QBMAN_MC_ACQUIRE);
	if (unlikely(!r)) {
		pr_err("qbman: acquire from BPID %d failed, no response\n",
		       bpid);
		return -EIO;
	}

	/* Decode the outcome */
	WARN_ON((r->verb & 0x7f) != QBMAN_MC_ACQUIRE);

	/* Determine success or failure */
	if (unlikely(r->rslt != QBMAN_MC_RSLT_OK)) {
		pr_err("qbman: acquire from BPID 0x%x failed, code=0x%02x\n",
		       bpid, r->rslt);
		return -EIO;
	}

	WARN_ON(r->num > num_buffers);

	/* Copy the acquired buffers to the caller's array */
	for (i = 0; i < r->num; i++)
		buffers[i] = le64_to_cpu(r->buf[i]);

	return (int)r->num;
}