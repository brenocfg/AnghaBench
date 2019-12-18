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
struct rpc {int result; int /*<<< orphan*/  complete; int /*<<< orphan*/  list; } ;
struct era {int /*<<< orphan*/  rpc_lock; int /*<<< orphan*/  rpc_calls; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_worker (struct era*) ; 

__attribute__((used)) static int perform_rpc(struct era *era, struct rpc *rpc)
{
	rpc->result = 0;
	init_completion(&rpc->complete);

	spin_lock(&era->rpc_lock);
	list_add(&rpc->list, &era->rpc_calls);
	spin_unlock(&era->rpc_lock);

	wake_worker(era);
	wait_for_completion(&rpc->complete);

	return rpc->result;
}