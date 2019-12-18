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
struct netdev_bpf {int command; } ;
struct net_device {int dummy; } ;
struct cpsw_priv {int /*<<< orphan*/  xdpi; } ;

/* Variables and functions */
 int EINVAL ; 
#define  XDP_QUERY_PROG 129 
#define  XDP_SETUP_PROG 128 
 int cpsw_xdp_prog_setup (struct cpsw_priv*,struct netdev_bpf*) ; 
 struct cpsw_priv* netdev_priv (struct net_device*) ; 
 int xdp_attachment_query (int /*<<< orphan*/ *,struct netdev_bpf*) ; 

__attribute__((used)) static int cpsw_ndo_bpf(struct net_device *ndev, struct netdev_bpf *bpf)
{
	struct cpsw_priv *priv = netdev_priv(ndev);

	switch (bpf->command) {
	case XDP_SETUP_PROG:
		return cpsw_xdp_prog_setup(priv, bpf);

	case XDP_QUERY_PROG:
		return xdp_attachment_query(&priv->xdpi, bpf);

	default:
		return -EINVAL;
	}
}