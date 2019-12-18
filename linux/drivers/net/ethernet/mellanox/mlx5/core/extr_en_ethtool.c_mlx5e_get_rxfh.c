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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct mlx5e_rss_params {int /*<<< orphan*/  hfunc; int /*<<< orphan*/  toeplitz_hash_key; int /*<<< orphan*/  indirection_rqt; } ;
struct mlx5e_priv {struct mlx5e_rss_params rss_params; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int mlx5e_get_rxfh(struct net_device *netdev, u32 *indir, u8 *key,
			  u8 *hfunc)
{
	struct mlx5e_priv *priv = netdev_priv(netdev);
	struct mlx5e_rss_params *rss = &priv->rss_params;

	if (indir)
		memcpy(indir, rss->indirection_rqt,
		       sizeof(rss->indirection_rqt));

	if (key)
		memcpy(key, rss->toeplitz_hash_key,
		       sizeof(rss->toeplitz_hash_key));

	if (hfunc)
		*hfunc = rss->hfunc;

	return 0;
}