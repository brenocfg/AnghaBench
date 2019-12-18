#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_8__ {int next_idx; int dqrr_size; int valid_bit; scalar_t__ reset_bug; } ;
struct TYPE_7__ {int /*<<< orphan*/  available; } ;
struct qbman_swp {TYPE_4__ dqrr; TYPE_3__ vdq; TYPE_1__* desc; } ;
struct TYPE_6__ {int verb; int stat; } ;
typedef  struct dpaa2_dq {TYPE_2__ dq; } const dpaa2_dq ;
struct TYPE_5__ {int qman_version; } ;

/* Variables and functions */
 int DPAA2_DQ_STAT_EXPIRED ; 
 int DPAA2_DQ_STAT_VOLATILE ; 
 int /*<<< orphan*/  QBMAN_CENA_SWP_DQRR (int) ; 
 int /*<<< orphan*/  QBMAN_CENA_SWP_DQRR_MEM (int) ; 
 int /*<<< orphan*/  QBMAN_CINH_SWP_DQPI ; 
 int QBMAN_RESULT_DQ ; 
 int QBMAN_RESULT_MASK ; 
 int QB_VALID_BIT ; 
 int QMAN_DQRR_PI_MASK ; 
 int QMAN_REV_5000 ; 
 int QMAN_REV_MASK ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int) ; 
 int /*<<< orphan*/  prefetch (struct dpaa2_dq const*) ; 
 struct dpaa2_dq const* qbman_get_cmd (struct qbman_swp*,int /*<<< orphan*/ ) ; 
 int qbman_read_register (struct qbman_swp*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (scalar_t__) ; 

const struct dpaa2_dq *qbman_swp_dqrr_next(struct qbman_swp *s)
{
	u32 verb;
	u32 response_verb;
	u32 flags;
	struct dpaa2_dq *p;

	/* Before using valid-bit to detect if something is there, we have to
	 * handle the case of the DQRR reset bug...
	 */
	if (unlikely(s->dqrr.reset_bug)) {
		/*
		 * We pick up new entries by cache-inhibited producer index,
		 * which means that a non-coherent mapping would require us to
		 * invalidate and read *only* once that PI has indicated that
		 * there's an entry here. The first trip around the DQRR ring
		 * will be much less efficient than all subsequent trips around
		 * it...
		 */
		u8 pi = qbman_read_register(s, QBMAN_CINH_SWP_DQPI) &
			QMAN_DQRR_PI_MASK;

		/* there are new entries if pi != next_idx */
		if (pi == s->dqrr.next_idx)
			return NULL;

		/*
		 * if next_idx is/was the last ring index, and 'pi' is
		 * different, we can disable the workaround as all the ring
		 * entries have now been DMA'd to so valid-bit checking is
		 * repaired. Note: this logic needs to be based on next_idx
		 * (which increments one at a time), rather than on pi (which
		 * can burst and wrap-around between our snapshots of it).
		 */
		if (s->dqrr.next_idx == (s->dqrr.dqrr_size - 1)) {
			pr_debug("next_idx=%d, pi=%d, clear reset bug\n",
				 s->dqrr.next_idx, pi);
			s->dqrr.reset_bug = 0;
		}
		prefetch(qbman_get_cmd(s,
				       QBMAN_CENA_SWP_DQRR(s->dqrr.next_idx)));
	}

	if ((s->desc->qman_version & QMAN_REV_MASK) < QMAN_REV_5000)
		p = qbman_get_cmd(s, QBMAN_CENA_SWP_DQRR(s->dqrr.next_idx));
	else
		p = qbman_get_cmd(s, QBMAN_CENA_SWP_DQRR_MEM(s->dqrr.next_idx));
	verb = p->dq.verb;

	/*
	 * If the valid-bit isn't of the expected polarity, nothing there. Note,
	 * in the DQRR reset bug workaround, we shouldn't need to skip these
	 * check, because we've already determined that a new entry is available
	 * and we've invalidated the cacheline before reading it, so the
	 * valid-bit behaviour is repaired and should tell us what we already
	 * knew from reading PI.
	 */
	if ((verb & QB_VALID_BIT) != s->dqrr.valid_bit) {
		prefetch(qbman_get_cmd(s,
				       QBMAN_CENA_SWP_DQRR(s->dqrr.next_idx)));
		return NULL;
	}
	/*
	 * There's something there. Move "next_idx" attention to the next ring
	 * entry (and prefetch it) before returning what we found.
	 */
	s->dqrr.next_idx++;
	s->dqrr.next_idx &= s->dqrr.dqrr_size - 1; /* Wrap around */
	if (!s->dqrr.next_idx)
		s->dqrr.valid_bit ^= QB_VALID_BIT;

	/*
	 * If this is the final response to a volatile dequeue command
	 * indicate that the vdq is available
	 */
	flags = p->dq.stat;
	response_verb = verb & QBMAN_RESULT_MASK;
	if ((response_verb == QBMAN_RESULT_DQ) &&
	    (flags & DPAA2_DQ_STAT_VOLATILE) &&
	    (flags & DPAA2_DQ_STAT_EXPIRED))
		atomic_inc(&s->vdq.available);

	prefetch(qbman_get_cmd(s, QBMAN_CENA_SWP_DQRR(s->dqrr.next_idx)));

	return p;
}