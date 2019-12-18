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
struct TYPE_4__ {int /*<<< orphan*/  irq_vector; } ;

/* Variables and functions */
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_net_close_free_all (struct nfp_net*) ; 
 int nfp_net_open_alloc_all (struct nfp_net*) ; 
 int nfp_net_set_config_and_enable (struct nfp_net*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

int nfp_ctrl_open(struct nfp_net *nn)
{
	int err, r;

	/* ring dumping depends on vNICs being opened/closed under rtnl */
	rtnl_lock();

	err = nfp_net_open_alloc_all(nn);
	if (err)
		goto err_unlock;

	err = nfp_net_set_config_and_enable(nn);
	if (err)
		goto err_free_all;

	for (r = 0; r < nn->dp.num_r_vecs; r++)
		enable_irq(nn->r_vecs[r].irq_vector);

	rtnl_unlock();

	return 0;

err_free_all:
	nfp_net_close_free_all(nn);
err_unlock:
	rtnl_unlock();
	return err;
}