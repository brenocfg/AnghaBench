#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ aalgo; scalar_t__ ealgo; scalar_t__ calgo; int flags; scalar_t__ family; scalar_t__ mode; } ;
struct TYPE_6__ {scalar_t__ proto; } ;
struct TYPE_5__ {struct net_device* dev; } ;
struct xfrm_state {TYPE_4__ props; int /*<<< orphan*/  geniv; scalar_t__ tfcpad; TYPE_3__* aead; scalar_t__ encap; TYPE_2__ id; TYPE_1__ xso; } ;
struct net_device {int /*<<< orphan*/  dev; } ;
struct mlx5e_priv {int /*<<< orphan*/  mdev; } ;
struct TYPE_7__ {int alg_icv_len; int alg_key_len; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int EINVAL ; 
 scalar_t__ IPPROTO_ESP ; 
 int MLX5_ACCEL_IPSEC_CAP_ESN ; 
 int MLX5_ACCEL_IPSEC_CAP_IPV6 ; 
 scalar_t__ SADB_AALG_NONE ; 
 scalar_t__ SADB_X_CALG_NONE ; 
 scalar_t__ SADB_X_EALG_AES_GCM_ICV16 ; 
 scalar_t__ XFRM_MODE_TRANSPORT ; 
 scalar_t__ XFRM_MODE_TUNNEL ; 
 int XFRM_STATE_ESN ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int mlx5_accel_ipsec_device_caps (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*) ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static inline int mlx5e_xfrm_validate_state(struct xfrm_state *x)
{
	struct net_device *netdev = x->xso.dev;
	struct mlx5e_priv *priv;

	priv = netdev_priv(netdev);

	if (x->props.aalgo != SADB_AALG_NONE) {
		netdev_info(netdev, "Cannot offload authenticated xfrm states\n");
		return -EINVAL;
	}
	if (x->props.ealgo != SADB_X_EALG_AES_GCM_ICV16) {
		netdev_info(netdev, "Only AES-GCM-ICV16 xfrm state may be offloaded\n");
		return -EINVAL;
	}
	if (x->props.calgo != SADB_X_CALG_NONE) {
		netdev_info(netdev, "Cannot offload compressed xfrm states\n");
		return -EINVAL;
	}
	if (x->props.flags & XFRM_STATE_ESN &&
	    !(mlx5_accel_ipsec_device_caps(priv->mdev) &
	    MLX5_ACCEL_IPSEC_CAP_ESN)) {
		netdev_info(netdev, "Cannot offload ESN xfrm states\n");
		return -EINVAL;
	}
	if (x->props.family != AF_INET &&
	    x->props.family != AF_INET6) {
		netdev_info(netdev, "Only IPv4/6 xfrm states may be offloaded\n");
		return -EINVAL;
	}
	if (x->props.mode != XFRM_MODE_TRANSPORT &&
	    x->props.mode != XFRM_MODE_TUNNEL) {
		dev_info(&netdev->dev, "Only transport and tunnel xfrm states may be offloaded\n");
		return -EINVAL;
	}
	if (x->id.proto != IPPROTO_ESP) {
		netdev_info(netdev, "Only ESP xfrm state may be offloaded\n");
		return -EINVAL;
	}
	if (x->encap) {
		netdev_info(netdev, "Encapsulated xfrm state may not be offloaded\n");
		return -EINVAL;
	}
	if (!x->aead) {
		netdev_info(netdev, "Cannot offload xfrm states without aead\n");
		return -EINVAL;
	}
	if (x->aead->alg_icv_len != 128) {
		netdev_info(netdev, "Cannot offload xfrm states with AEAD ICV length other than 128bit\n");
		return -EINVAL;
	}
	if ((x->aead->alg_key_len != 128 + 32) &&
	    (x->aead->alg_key_len != 256 + 32)) {
		netdev_info(netdev, "Cannot offload xfrm states with AEAD key length other than 128/256 bit\n");
		return -EINVAL;
	}
	if (x->tfcpad) {
		netdev_info(netdev, "Cannot offload xfrm states with tfc padding\n");
		return -EINVAL;
	}
	if (!x->geniv) {
		netdev_info(netdev, "Cannot offload xfrm states without geniv\n");
		return -EINVAL;
	}
	if (strcmp(x->geniv, "seqiv")) {
		netdev_info(netdev, "Cannot offload xfrm states with geniv other than seqiv\n");
		return -EINVAL;
	}
	if (x->props.family == AF_INET6 &&
	    !(mlx5_accel_ipsec_device_caps(priv->mdev) &
	     MLX5_ACCEL_IPSEC_CAP_IPV6)) {
		netdev_info(netdev, "IPv6 xfrm state offload is not supported by this device\n");
		return -EINVAL;
	}
	return 0;
}