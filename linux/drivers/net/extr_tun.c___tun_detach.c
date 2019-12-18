#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u16 ;
struct tun_struct {size_t numqueues; scalar_t__ numdisabled; int flags; TYPE_1__* dev; int /*<<< orphan*/ ** tfiles; } ;
struct tun_file {size_t queue_index; int /*<<< orphan*/  sk; int /*<<< orphan*/  tx_ring; int /*<<< orphan*/  xdp_rxq; scalar_t__ detached; int /*<<< orphan*/ * tun; } ;
struct TYPE_3__ {scalar_t__ reg_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int IFF_PERSIST ; 
 scalar_t__ NETREG_REGISTERED ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_carrier_off (TYPE_1__*) ; 
 int /*<<< orphan*/  ptr_ring_cleanup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* rtnl_dereference (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_net () ; 
 int /*<<< orphan*/  tun_disable_queue (struct tun_struct*,struct tun_file*) ; 
 struct tun_struct* tun_enable_queue (struct tun_file*) ; 
 int /*<<< orphan*/  tun_flow_delete_by_queue (struct tun_struct*,int) ; 
 int /*<<< orphan*/  tun_napi_del (struct tun_file*) ; 
 int /*<<< orphan*/  tun_napi_disable (struct tun_file*) ; 
 int /*<<< orphan*/  tun_ptr_free ; 
 int /*<<< orphan*/  tun_queue_purge (struct tun_file*) ; 
 int /*<<< orphan*/  tun_set_real_num_queues (struct tun_struct*) ; 
 int /*<<< orphan*/  unregister_netdevice (TYPE_1__*) ; 
 int /*<<< orphan*/  xdp_rxq_info_unreg (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __tun_detach(struct tun_file *tfile, bool clean)
{
	struct tun_file *ntfile;
	struct tun_struct *tun;

	tun = rtnl_dereference(tfile->tun);

	if (tun && clean) {
		tun_napi_disable(tfile);
		tun_napi_del(tfile);
	}

	if (tun && !tfile->detached) {
		u16 index = tfile->queue_index;
		BUG_ON(index >= tun->numqueues);

		rcu_assign_pointer(tun->tfiles[index],
				   tun->tfiles[tun->numqueues - 1]);
		ntfile = rtnl_dereference(tun->tfiles[index]);
		ntfile->queue_index = index;
		rcu_assign_pointer(tun->tfiles[tun->numqueues - 1],
				   NULL);

		--tun->numqueues;
		if (clean) {
			RCU_INIT_POINTER(tfile->tun, NULL);
			sock_put(&tfile->sk);
		} else
			tun_disable_queue(tun, tfile);

		synchronize_net();
		tun_flow_delete_by_queue(tun, tun->numqueues + 1);
		/* Drop read queue */
		tun_queue_purge(tfile);
		tun_set_real_num_queues(tun);
	} else if (tfile->detached && clean) {
		tun = tun_enable_queue(tfile);
		sock_put(&tfile->sk);
	}

	if (clean) {
		if (tun && tun->numqueues == 0 && tun->numdisabled == 0) {
			netif_carrier_off(tun->dev);

			if (!(tun->flags & IFF_PERSIST) &&
			    tun->dev->reg_state == NETREG_REGISTERED)
				unregister_netdevice(tun->dev);
		}
		if (tun)
			xdp_rxq_info_unreg(&tfile->xdp_rxq);
		ptr_ring_cleanup(&tfile->tx_ring, tun_ptr_free);
		sock_put(&tfile->sk);
	}
}