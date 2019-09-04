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
struct TYPE_2__ {int key_len; int mask_len; scalar_t__ flags; } ;
struct nfp_fl_payload {int ingress_offload; struct nfp_fl_payload* unmasked_data; struct nfp_fl_payload* mask_data; int /*<<< orphan*/  lock; TYPE_1__ meta; scalar_t__ nfp_tun_ipv4_addr; void* action_data; } ;
struct nfp_fl_key_ls {int key_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int NFP_FL_MAX_A_SIZ ; 
 int /*<<< orphan*/  kfree (struct nfp_fl_payload*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct nfp_fl_payload *
nfp_flower_allocate_new(struct nfp_fl_key_ls *key_layer, bool egress)
{
	struct nfp_fl_payload *flow_pay;

	flow_pay = kmalloc(sizeof(*flow_pay), GFP_KERNEL);
	if (!flow_pay)
		return NULL;

	flow_pay->meta.key_len = key_layer->key_size;
	flow_pay->unmasked_data = kmalloc(key_layer->key_size, GFP_KERNEL);
	if (!flow_pay->unmasked_data)
		goto err_free_flow;

	flow_pay->meta.mask_len = key_layer->key_size;
	flow_pay->mask_data = kmalloc(key_layer->key_size, GFP_KERNEL);
	if (!flow_pay->mask_data)
		goto err_free_unmasked;

	flow_pay->action_data = kmalloc(NFP_FL_MAX_A_SIZ, GFP_KERNEL);
	if (!flow_pay->action_data)
		goto err_free_mask;

	flow_pay->nfp_tun_ipv4_addr = 0;
	flow_pay->meta.flags = 0;
	spin_lock_init(&flow_pay->lock);

	flow_pay->ingress_offload = !egress;

	return flow_pay;

err_free_mask:
	kfree(flow_pay->mask_data);
err_free_unmasked:
	kfree(flow_pay->unmasked_data);
err_free_flow:
	kfree(flow_pay);
	return NULL;
}