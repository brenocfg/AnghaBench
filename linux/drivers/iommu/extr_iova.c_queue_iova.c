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
struct iova_fq {int /*<<< orphan*/  lock; TYPE_1__* entries; } ;
struct iova_domain {int /*<<< orphan*/  fq_timer; int /*<<< orphan*/  fq_timer_on; int /*<<< orphan*/  fq_flush_start_cnt; int /*<<< orphan*/  fq; } ;
struct TYPE_2__ {unsigned long iova_pfn; unsigned long pages; unsigned long data; int /*<<< orphan*/  counter; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOVA_FQ_TIMEOUT ; 
 int /*<<< orphan*/  atomic64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_cmpxchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ fq_full (struct iova_fq*) ; 
 unsigned int fq_ring_add (struct iova_fq*) ; 
 int /*<<< orphan*/  fq_ring_free (struct iova_domain*,struct iova_fq*) ; 
 int /*<<< orphan*/  iova_domain_flush (struct iova_domain*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 struct iova_fq* raw_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void queue_iova(struct iova_domain *iovad,
		unsigned long pfn, unsigned long pages,
		unsigned long data)
{
	struct iova_fq *fq = raw_cpu_ptr(iovad->fq);
	unsigned long flags;
	unsigned idx;

	spin_lock_irqsave(&fq->lock, flags);

	/*
	 * First remove all entries from the flush queue that have already been
	 * flushed out on another CPU. This makes the fq_full() check below less
	 * likely to be true.
	 */
	fq_ring_free(iovad, fq);

	if (fq_full(fq)) {
		iova_domain_flush(iovad);
		fq_ring_free(iovad, fq);
	}

	idx = fq_ring_add(fq);

	fq->entries[idx].iova_pfn = pfn;
	fq->entries[idx].pages    = pages;
	fq->entries[idx].data     = data;
	fq->entries[idx].counter  = atomic64_read(&iovad->fq_flush_start_cnt);

	spin_unlock_irqrestore(&fq->lock, flags);

	/* Avoid false sharing as much as possible. */
	if (!atomic_read(&iovad->fq_timer_on) &&
	    !atomic_cmpxchg(&iovad->fq_timer_on, 0, 1))
		mod_timer(&iovad->fq_timer,
			  jiffies + msecs_to_jiffies(IOVA_FQ_TIMEOUT));
}