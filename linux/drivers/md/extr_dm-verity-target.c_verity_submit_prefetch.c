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
struct dm_verity_prefetch_work {int /*<<< orphan*/  work; int /*<<< orphan*/  n_blocks; int /*<<< orphan*/  block; struct dm_verity* v; } ;
struct dm_verity_io {int /*<<< orphan*/  n_blocks; int /*<<< orphan*/  block; } ;
struct dm_verity {int /*<<< orphan*/  verify_wq; } ;

/* Variables and functions */
 int GFP_NOIO ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int __GFP_NOMEMALLOC ; 
 int __GFP_NORETRY ; 
 int __GFP_NOWARN ; 
 struct dm_verity_prefetch_work* kmalloc (int,int) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  verity_prefetch_io ; 

__attribute__((used)) static void verity_submit_prefetch(struct dm_verity *v, struct dm_verity_io *io)
{
	struct dm_verity_prefetch_work *pw;

	pw = kmalloc(sizeof(struct dm_verity_prefetch_work),
		GFP_NOIO | __GFP_NORETRY | __GFP_NOMEMALLOC | __GFP_NOWARN);

	if (!pw)
		return;

	INIT_WORK(&pw->work, verity_prefetch_io);
	pw->v = v;
	pw->block = io->block;
	pw->n_blocks = io->n_blocks;
	queue_work(v->verify_wq, &pw->work);
}