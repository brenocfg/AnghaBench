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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  rss_hfunc; int /*<<< orphan*/  toeplitz_hash_key; int /*<<< orphan*/  indirection_rqt; } ;
struct TYPE_4__ {TYPE_1__ params; } ;
struct mlx5e_priv {TYPE_2__ channels; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int mlx5e_get_rxfh(struct net_device *netdev, u32 *indir, u8 *key,
			  u8 *hfunc)
{
	struct mlx5e_priv *priv = netdev_priv(netdev);

	if (indir)
		memcpy(indir, priv->channels.params.indirection_rqt,
		       sizeof(priv->channels.params.indirection_rqt));

	if (key)
		memcpy(key, priv->channels.params.toeplitz_hash_key,
		       sizeof(priv->channels.params.toeplitz_hash_key));

	if (hfunc)
		*hfunc = priv->channels.params.rss_hfunc;

	return 0;
}