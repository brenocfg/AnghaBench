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
struct TYPE_3__ {int num_r_vecs; } ;
struct nfp_net {TYPE_2__* r_vecs; TYPE_1__ dp; } ;
struct TYPE_4__ {int /*<<< orphan*/  tasklet; int /*<<< orphan*/  irq_vector; } ;

/* Variables and functions */
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_net_clear_config_and_disable (struct nfp_net*) ; 
 int /*<<< orphan*/  nfp_net_close_free_all (struct nfp_net*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  tasklet_disable (int /*<<< orphan*/ *) ; 

void nfp_ctrl_close(struct nfp_net *nn)
{
	int r;

	rtnl_lock();

	for (r = 0; r < nn->dp.num_r_vecs; r++) {
		disable_irq(nn->r_vecs[r].irq_vector);
		tasklet_disable(&nn->r_vecs[r].tasklet);
	}

	nfp_net_clear_config_and_disable(nn);

	nfp_net_close_free_all(nn);

	rtnl_unlock();
}