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
typedef  int u8 ;
struct qman_portal {int /*<<< orphan*/  p; scalar_t__ use_eqcr_ci_stashing; } ;
struct qman_fq {int /*<<< orphan*/  fqid; } ;
struct qm_fd {int dummy; } ;
struct qm_eqcr_entry {struct qm_fd fd; int /*<<< orphan*/  tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  QM_EQCR_VERB_CMD_ENQUEUE ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fq_to_tag (struct qman_fq*) ; 
 struct qman_portal* get_affine_portal () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  put_affine_portal () ; 
 int qm_eqcr_get_avail (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qm_eqcr_pvb_commit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct qm_eqcr_entry* qm_eqcr_start_no_stash (int /*<<< orphan*/ *) ; 
 struct qm_eqcr_entry* qm_eqcr_start_stash (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qm_fqid_set (struct qm_eqcr_entry*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  update_eqcr_ci (struct qman_portal*,int) ; 

int qman_enqueue(struct qman_fq *fq, const struct qm_fd *fd)
{
	struct qman_portal *p;
	struct qm_eqcr_entry *eq;
	unsigned long irqflags;
	u8 avail;

	p = get_affine_portal();
	local_irq_save(irqflags);

	if (p->use_eqcr_ci_stashing) {
		/*
		 * The stashing case is easy, only update if we need to in
		 * order to try and liberate ring entries.
		 */
		eq = qm_eqcr_start_stash(&p->p);
	} else {
		/*
		 * The non-stashing case is harder, need to prefetch ahead of
		 * time.
		 */
		avail = qm_eqcr_get_avail(&p->p);
		if (avail < 2)
			update_eqcr_ci(p, avail);
		eq = qm_eqcr_start_no_stash(&p->p);
	}

	if (unlikely(!eq))
		goto out;

	qm_fqid_set(eq, fq->fqid);
	eq->tag = cpu_to_be32(fq_to_tag(fq));
	eq->fd = *fd;

	qm_eqcr_pvb_commit(&p->p, QM_EQCR_VERB_CMD_ENQUEUE);
out:
	local_irq_restore(irqflags);
	put_affine_portal();
	return 0;
}