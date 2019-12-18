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
struct TYPE_2__ {scalar_t__ target2; scalar_t__ target; } ;
struct stripe_head {int disks; scalar_t__ check_state; struct r5conf* raid_conf; struct r5dev* dev; int /*<<< orphan*/  batch_head; TYPE_1__ ops; } ;
struct raid5_percpu {int dummy; } ;
struct r5dev {int /*<<< orphan*/  flags; } ;
struct r5conf {int level; int /*<<< orphan*/  wait_for_overlap; int /*<<< orphan*/  percpu; } ;
struct dma_async_tx_descriptor {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  R5_Overlap ; 
 int /*<<< orphan*/  STRIPE_OP_BIODRAIN ; 
 int /*<<< orphan*/  STRIPE_OP_BIOFILL ; 
 int /*<<< orphan*/  STRIPE_OP_CHECK ; 
 int /*<<< orphan*/  STRIPE_OP_COMPUTE_BLK ; 
 int /*<<< orphan*/  STRIPE_OP_PARTIAL_PARITY ; 
 int /*<<< orphan*/  STRIPE_OP_PREXOR ; 
 int /*<<< orphan*/  STRIPE_OP_RECONSTRUCT ; 
 int /*<<< orphan*/  async_tx_ack (struct dma_async_tx_descriptor*) ; 
 scalar_t__ check_state_run ; 
 scalar_t__ check_state_run_pq ; 
 scalar_t__ check_state_run_q ; 
 unsigned long get_cpu () ; 
 struct dma_async_tx_descriptor* ops_run_biodrain (struct stripe_head*,struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  ops_run_biofill (struct stripe_head*) ; 
 int /*<<< orphan*/  ops_run_check_p (struct stripe_head*,struct raid5_percpu*) ; 
 int /*<<< orphan*/  ops_run_check_pq (struct stripe_head*,struct raid5_percpu*,int) ; 
 struct dma_async_tx_descriptor* ops_run_compute5 (struct stripe_head*,struct raid5_percpu*) ; 
 struct dma_async_tx_descriptor* ops_run_compute6_1 (struct stripe_head*,struct raid5_percpu*) ; 
 struct dma_async_tx_descriptor* ops_run_compute6_2 (struct stripe_head*,struct raid5_percpu*) ; 
 struct dma_async_tx_descriptor* ops_run_partial_parity (struct stripe_head*,struct raid5_percpu*,struct dma_async_tx_descriptor*) ; 
 struct dma_async_tx_descriptor* ops_run_prexor5 (struct stripe_head*,struct raid5_percpu*,struct dma_async_tx_descriptor*) ; 
 struct dma_async_tx_descriptor* ops_run_prexor6 (struct stripe_head*,struct raid5_percpu*,struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  ops_run_reconstruct5 (struct stripe_head*,struct raid5_percpu*,struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  ops_run_reconstruct6 (struct stripe_head*,struct raid5_percpu*,struct dma_async_tx_descriptor*) ; 
 struct raid5_percpu* per_cpu_ptr (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  put_cpu () ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void raid_run_ops(struct stripe_head *sh, unsigned long ops_request)
{
	int overlap_clear = 0, i, disks = sh->disks;
	struct dma_async_tx_descriptor *tx = NULL;
	struct r5conf *conf = sh->raid_conf;
	int level = conf->level;
	struct raid5_percpu *percpu;
	unsigned long cpu;

	cpu = get_cpu();
	percpu = per_cpu_ptr(conf->percpu, cpu);
	if (test_bit(STRIPE_OP_BIOFILL, &ops_request)) {
		ops_run_biofill(sh);
		overlap_clear++;
	}

	if (test_bit(STRIPE_OP_COMPUTE_BLK, &ops_request)) {
		if (level < 6)
			tx = ops_run_compute5(sh, percpu);
		else {
			if (sh->ops.target2 < 0 || sh->ops.target < 0)
				tx = ops_run_compute6_1(sh, percpu);
			else
				tx = ops_run_compute6_2(sh, percpu);
		}
		/* terminate the chain if reconstruct is not set to be run */
		if (tx && !test_bit(STRIPE_OP_RECONSTRUCT, &ops_request))
			async_tx_ack(tx);
	}

	if (test_bit(STRIPE_OP_PREXOR, &ops_request)) {
		if (level < 6)
			tx = ops_run_prexor5(sh, percpu, tx);
		else
			tx = ops_run_prexor6(sh, percpu, tx);
	}

	if (test_bit(STRIPE_OP_PARTIAL_PARITY, &ops_request))
		tx = ops_run_partial_parity(sh, percpu, tx);

	if (test_bit(STRIPE_OP_BIODRAIN, &ops_request)) {
		tx = ops_run_biodrain(sh, tx);
		overlap_clear++;
	}

	if (test_bit(STRIPE_OP_RECONSTRUCT, &ops_request)) {
		if (level < 6)
			ops_run_reconstruct5(sh, percpu, tx);
		else
			ops_run_reconstruct6(sh, percpu, tx);
	}

	if (test_bit(STRIPE_OP_CHECK, &ops_request)) {
		if (sh->check_state == check_state_run)
			ops_run_check_p(sh, percpu);
		else if (sh->check_state == check_state_run_q)
			ops_run_check_pq(sh, percpu, 0);
		else if (sh->check_state == check_state_run_pq)
			ops_run_check_pq(sh, percpu, 1);
		else
			BUG();
	}

	if (overlap_clear && !sh->batch_head)
		for (i = disks; i--; ) {
			struct r5dev *dev = &sh->dev[i];
			if (test_and_clear_bit(R5_Overlap, &dev->flags))
				wake_up(&sh->raid_conf->wait_for_overlap);
		}
	put_cpu();
}