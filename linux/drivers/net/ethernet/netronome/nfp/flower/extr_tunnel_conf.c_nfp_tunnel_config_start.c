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
struct TYPE_4__ {int /*<<< orphan*/  notifier_call; } ;
struct TYPE_3__ {int /*<<< orphan*/  offloaded_macs; TYPE_2__ neigh_nb; int /*<<< orphan*/  neigh_off_list; int /*<<< orphan*/  neigh_off_lock; int /*<<< orphan*/  ipv4_off_list; int /*<<< orphan*/  ipv4_off_lock; int /*<<< orphan*/  mac_off_ids; } ;
struct nfp_flower_priv {TYPE_1__ tun; } ;
struct nfp_app {struct nfp_flower_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ida_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfp_check_rhashtable_empty ; 
 int /*<<< orphan*/  nfp_tun_neigh_event_handler ; 
 int /*<<< orphan*/  offloaded_macs_params ; 
 int register_netevent_notifier (TYPE_2__*) ; 
 int /*<<< orphan*/  rhashtable_free_and_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int rhashtable_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int nfp_tunnel_config_start(struct nfp_app *app)
{
	struct nfp_flower_priv *priv = app->priv;
	int err;

	/* Initialise rhash for MAC offload tracking. */
	err = rhashtable_init(&priv->tun.offloaded_macs,
			      &offloaded_macs_params);
	if (err)
		return err;

	ida_init(&priv->tun.mac_off_ids);

	/* Initialise priv data for IPv4 offloading. */
	mutex_init(&priv->tun.ipv4_off_lock);
	INIT_LIST_HEAD(&priv->tun.ipv4_off_list);

	/* Initialise priv data for neighbour offloading. */
	spin_lock_init(&priv->tun.neigh_off_lock);
	INIT_LIST_HEAD(&priv->tun.neigh_off_list);
	priv->tun.neigh_nb.notifier_call = nfp_tun_neigh_event_handler;

	err = register_netevent_notifier(&priv->tun.neigh_nb);
	if (err) {
		rhashtable_free_and_destroy(&priv->tun.offloaded_macs,
					    nfp_check_rhashtable_empty, NULL);
		return err;
	}

	return 0;
}