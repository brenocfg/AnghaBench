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
struct ppl_conf {int /*<<< orphan*/  io_kc; int /*<<< orphan*/  io_pool; int /*<<< orphan*/  flush_bs; int /*<<< orphan*/  bs; struct ppl_conf* child_logs; TYPE_1__* mddev; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MD_HAS_MULTIPLE_PPLS ; 
 int /*<<< orphan*/  MD_HAS_PPL ; 
 int /*<<< orphan*/  bioset_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ppl_conf*) ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_exit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __ppl_exit_log(struct ppl_conf *ppl_conf)
{
	clear_bit(MD_HAS_PPL, &ppl_conf->mddev->flags);
	clear_bit(MD_HAS_MULTIPLE_PPLS, &ppl_conf->mddev->flags);

	kfree(ppl_conf->child_logs);

	bioset_exit(&ppl_conf->bs);
	bioset_exit(&ppl_conf->flush_bs);
	mempool_exit(&ppl_conf->io_pool);
	kmem_cache_destroy(ppl_conf->io_kc);

	kfree(ppl_conf);
}