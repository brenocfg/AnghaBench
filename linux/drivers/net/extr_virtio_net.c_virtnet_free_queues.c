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
struct virtnet_info {int max_queue_pairs; TYPE_1__* ctrl; TYPE_1__* sq; TYPE_1__* rq; } ;
struct TYPE_2__ {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  napi_hash_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_napi_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_net () ; 

__attribute__((used)) static void virtnet_free_queues(struct virtnet_info *vi)
{
	int i;

	for (i = 0; i < vi->max_queue_pairs; i++) {
		napi_hash_del(&vi->rq[i].napi);
		netif_napi_del(&vi->rq[i].napi);
		netif_napi_del(&vi->sq[i].napi);
	}

	/* We called napi_hash_del() before netif_napi_del(),
	 * we need to respect an RCU grace period before freeing vi->rq
	 */
	synchronize_net();

	kfree(vi->rq);
	kfree(vi->sq);
	kfree(vi->ctrl);
}