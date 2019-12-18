#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct iwl_txq {unsigned int n_window; int write_ptr; int read_ptr; } ;
struct iwl_trans {TYPE_2__* trans_cfg; } ;
struct TYPE_4__ {TYPE_1__* base_params; } ;
struct TYPE_3__ {unsigned int max_tfd_queue_size; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 

int iwl_queue_space(struct iwl_trans *trans, const struct iwl_txq *q)
{
	unsigned int max;
	unsigned int used;

	/*
	 * To avoid ambiguity between empty and completely full queues, there
	 * should always be less than max_tfd_queue_size elements in the queue.
	 * If q->n_window is smaller than max_tfd_queue_size, there is no need
	 * to reserve any queue entries for this purpose.
	 */
	if (q->n_window < trans->trans_cfg->base_params->max_tfd_queue_size)
		max = q->n_window;
	else
		max = trans->trans_cfg->base_params->max_tfd_queue_size - 1;

	/*
	 * max_tfd_queue_size is a power of 2, so the following is equivalent to
	 * modulo by max_tfd_queue_size and is well defined.
	 */
	used = (q->write_ptr - q->read_ptr) &
		(trans->trans_cfg->base_params->max_tfd_queue_size - 1);

	if (WARN_ON(used > max))
		return 0;

	return max - used;
}