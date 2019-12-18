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
struct nfp_app_bpf {int /*<<< orphan*/  bpf_dev; } ;
struct nfp_app {struct nfp_app_bpf* priv; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int bpf_offload_dev_netdev_register (int /*<<< orphan*/ ,struct net_device*) ; 

__attribute__((used)) static int nfp_bpf_ndo_init(struct nfp_app *app, struct net_device *netdev)
{
	struct nfp_app_bpf *bpf = app->priv;

	return bpf_offload_dev_netdev_register(bpf->bpf_dev, netdev);
}