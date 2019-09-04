#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  entry; } ;
typedef  TYPE_1__ wait_queue_entry_t ;
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;
struct sbq_wait_state {TYPE_2__ wait; } ;
struct sbitmap_queue {int dummy; } ;
struct kyber_queue_data {struct sbitmap_queue* domain_tokens; } ;
struct kyber_hctx_data {unsigned int cur_domain; struct sbq_wait_state** domain_ws; int /*<<< orphan*/ * wait_index; TYPE_1__* domain_wait; } ;
struct blk_mq_hw_ctx {int dummy; } ;

/* Variables and functions */
 int __sbitmap_queue_get (struct sbitmap_queue*) ; 
 int /*<<< orphan*/  add_wait_queue (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty_careful (int /*<<< orphan*/ *) ; 
 struct sbq_wait_state* sbq_wait_ptr (struct sbitmap_queue*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int kyber_get_domain_token(struct kyber_queue_data *kqd,
				  struct kyber_hctx_data *khd,
				  struct blk_mq_hw_ctx *hctx)
{
	unsigned int sched_domain = khd->cur_domain;
	struct sbitmap_queue *domain_tokens = &kqd->domain_tokens[sched_domain];
	wait_queue_entry_t *wait = &khd->domain_wait[sched_domain];
	struct sbq_wait_state *ws;
	int nr;

	nr = __sbitmap_queue_get(domain_tokens);

	/*
	 * If we failed to get a domain token, make sure the hardware queue is
	 * run when one becomes available. Note that this is serialized on
	 * khd->lock, but we still need to be careful about the waker.
	 */
	if (nr < 0 && list_empty_careful(&wait->entry)) {
		ws = sbq_wait_ptr(domain_tokens,
				  &khd->wait_index[sched_domain]);
		khd->domain_ws[sched_domain] = ws;
		add_wait_queue(&ws->wait, wait);

		/*
		 * Try again in case a token was freed before we got on the wait
		 * queue.
		 */
		nr = __sbitmap_queue_get(domain_tokens);
	}

	/*
	 * If we got a token while we were on the wait queue, remove ourselves
	 * from the wait queue to ensure that all wake ups make forward
	 * progress. It's possible that the waker already deleted the entry
	 * between the !list_empty_careful() check and us grabbing the lock, but
	 * list_del_init() is okay with that.
	 */
	if (nr >= 0 && !list_empty_careful(&wait->entry)) {
		ws = khd->domain_ws[sched_domain];
		spin_lock_irq(&ws->wait.lock);
		list_del_init(&wait->entry);
		spin_unlock_irq(&ws->wait.lock);
	}

	return nr;
}