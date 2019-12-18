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
typedef  int /*<<< orphan*/  u8 ;
struct nfp_tun_offloaded_mac {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  offloaded_macs; } ;
struct nfp_flower_priv {TYPE_1__ tun; } ;
struct nfp_app {struct nfp_flower_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  offloaded_macs_params ; 
 struct nfp_tun_offloaded_mac* rhashtable_lookup_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct nfp_tun_offloaded_mac *
nfp_tunnel_lookup_offloaded_macs(struct nfp_app *app, u8 *mac)
{
	struct nfp_flower_priv *priv = app->priv;

	return rhashtable_lookup_fast(&priv->tun.offloaded_macs, mac,
				      offloaded_macs_params);
}