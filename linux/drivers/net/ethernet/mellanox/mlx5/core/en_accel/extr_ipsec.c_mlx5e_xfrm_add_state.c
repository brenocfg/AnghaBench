#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int flags; unsigned long offload_handle; struct net_device* dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  a6; int /*<<< orphan*/  a4; } ;
struct TYPE_9__ {int /*<<< orphan*/  spi; TYPE_3__ daddr; } ;
struct TYPE_6__ {int /*<<< orphan*/  a6; int /*<<< orphan*/  a4; } ;
struct TYPE_7__ {int flags; scalar_t__ family; TYPE_1__ saddr; } ;
struct xfrm_state {TYPE_5__ xso; TYPE_4__ id; TYPE_2__ props; } ;
struct net_device {int dummy; } ;
struct mlx5e_priv {int /*<<< orphan*/  mdev; int /*<<< orphan*/  ipsec; } ;
struct mlx5e_ipsec_sa_entry {int /*<<< orphan*/  xfrm; int /*<<< orphan*/  hw_context; int /*<<< orphan*/  set_iv_op; int /*<<< orphan*/  ipsec; struct xfrm_state* x; } ;
struct mlx5_accel_esp_xfrm_attrs {int dummy; } ;
typedef  int /*<<< orphan*/  saddr ;
typedef  int /*<<< orphan*/  daddr ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_ACCEL_XFRM_FLAG_REQUIRE_METADATA ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int XFRM_OFFLOAD_INBOUND ; 
 int XFRM_STATE_ESN ; 
 int /*<<< orphan*/  kfree (struct mlx5e_ipsec_sa_entry*) ; 
 struct mlx5e_ipsec_sa_entry* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlx5_accel_esp_create_hw_context (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlx5_accel_esp_create_xfrm (int /*<<< orphan*/ ,struct mlx5_accel_esp_xfrm_attrs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_accel_esp_destroy_xfrm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_ipsec_build_accel_xfrm_attrs (struct mlx5e_ipsec_sa_entry*,struct mlx5_accel_esp_xfrm_attrs*) ; 
 int mlx5e_ipsec_sadb_rx_add (struct mlx5e_ipsec_sa_entry*) ; 
 int /*<<< orphan*/  mlx5e_ipsec_sadb_rx_del (struct mlx5e_ipsec_sa_entry*) ; 
 int /*<<< orphan*/  mlx5e_ipsec_sadb_rx_free (struct mlx5e_ipsec_sa_entry*) ; 
 int /*<<< orphan*/  mlx5e_ipsec_set_iv ; 
 int /*<<< orphan*/  mlx5e_ipsec_set_iv_esn ; 
 int /*<<< orphan*/  mlx5e_ipsec_update_esn_state (struct mlx5e_ipsec_sa_entry*) ; 
 int mlx5e_xfrm_validate_state (struct xfrm_state*) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,int) ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int mlx5e_xfrm_add_state(struct xfrm_state *x)
{
	struct mlx5e_ipsec_sa_entry *sa_entry = NULL;
	struct net_device *netdev = x->xso.dev;
	struct mlx5_accel_esp_xfrm_attrs attrs;
	struct mlx5e_priv *priv;
	__be32 saddr[4] = {0}, daddr[4] = {0}, spi;
	bool is_ipv6 = false;
	int err;

	priv = netdev_priv(netdev);

	err = mlx5e_xfrm_validate_state(x);
	if (err)
		return err;

	sa_entry = kzalloc(sizeof(*sa_entry), GFP_KERNEL);
	if (!sa_entry) {
		err = -ENOMEM;
		goto out;
	}

	sa_entry->x = x;
	sa_entry->ipsec = priv->ipsec;

	/* Add the SA to handle processed incoming packets before the add SA
	 * completion was received
	 */
	if (x->xso.flags & XFRM_OFFLOAD_INBOUND) {
		err = mlx5e_ipsec_sadb_rx_add(sa_entry);
		if (err) {
			netdev_info(netdev, "Failed adding to SADB_RX: %d\n", err);
			goto err_entry;
		}
	} else {
		sa_entry->set_iv_op = (x->props.flags & XFRM_STATE_ESN) ?
				mlx5e_ipsec_set_iv_esn : mlx5e_ipsec_set_iv;
	}

	/* check esn */
	mlx5e_ipsec_update_esn_state(sa_entry);

	/* create xfrm */
	mlx5e_ipsec_build_accel_xfrm_attrs(sa_entry, &attrs);
	sa_entry->xfrm =
		mlx5_accel_esp_create_xfrm(priv->mdev, &attrs,
					   MLX5_ACCEL_XFRM_FLAG_REQUIRE_METADATA);
	if (IS_ERR(sa_entry->xfrm)) {
		err = PTR_ERR(sa_entry->xfrm);
		goto err_sadb_rx;
	}

	/* create hw context */
	if (x->props.family == AF_INET) {
		saddr[3] = x->props.saddr.a4;
		daddr[3] = x->id.daddr.a4;
	} else {
		memcpy(saddr, x->props.saddr.a6, sizeof(saddr));
		memcpy(daddr, x->id.daddr.a6, sizeof(daddr));
		is_ipv6 = true;
	}
	spi = x->id.spi;
	sa_entry->hw_context =
			mlx5_accel_esp_create_hw_context(priv->mdev,
							 sa_entry->xfrm,
							 saddr, daddr, spi,
							 is_ipv6);
	if (IS_ERR(sa_entry->hw_context)) {
		err = PTR_ERR(sa_entry->hw_context);
		goto err_xfrm;
	}

	x->xso.offload_handle = (unsigned long)sa_entry;
	goto out;

err_xfrm:
	mlx5_accel_esp_destroy_xfrm(sa_entry->xfrm);
err_sadb_rx:
	if (x->xso.flags & XFRM_OFFLOAD_INBOUND) {
		mlx5e_ipsec_sadb_rx_del(sa_entry);
		mlx5e_ipsec_sadb_rx_free(sa_entry);
	}
err_entry:
	kfree(sa_entry);
out:
	return err;
}