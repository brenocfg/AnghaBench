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
typedef  size_t u32 ;
struct rcar_canfd_global {struct rcar_canfd_channel** ch; } ;
struct rcar_canfd_channel {int /*<<< orphan*/  ndev; int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_candev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_napi_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_candev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rcar_canfd_channel_remove(struct rcar_canfd_global *gpriv, u32 ch)
{
	struct rcar_canfd_channel *priv = gpriv->ch[ch];

	if (priv) {
		unregister_candev(priv->ndev);
		netif_napi_del(&priv->napi);
		free_candev(priv->ndev);
	}
}