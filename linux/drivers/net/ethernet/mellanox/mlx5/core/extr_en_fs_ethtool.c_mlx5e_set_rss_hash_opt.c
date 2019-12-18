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
struct TYPE_2__ {int /*<<< orphan*/ * rx_hash_fields; } ;
struct mlx5e_priv {int /*<<< orphan*/  state_lock; TYPE_1__ rss_params; } ;
struct ethtool_rxnfc {scalar_t__ flow_type; int data; } ;
typedef  enum mlx5e_traffic_types { ____Placeholder_mlx5e_traffic_types } mlx5e_traffic_types ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MLX5E_NUM_INDIR_TIRS ; 
 int /*<<< orphan*/  MLX5_HASH_FIELD_SEL_DST_IP ; 
 int /*<<< orphan*/  MLX5_HASH_FIELD_SEL_L4_DPORT ; 
 int /*<<< orphan*/  MLX5_HASH_FIELD_SEL_L4_SPORT ; 
 int /*<<< orphan*/  MLX5_HASH_FIELD_SEL_SRC_IP ; 
 int MLX5_ST_SZ_BYTES (int /*<<< orphan*/ ) ; 
 int RXH_IP_DST ; 
 int RXH_IP_SRC ; 
 int RXH_L4_B_0_1 ; 
 int RXH_L4_B_2_3 ; 
 scalar_t__ TCP_V4_FLOW ; 
 scalar_t__ TCP_V6_FLOW ; 
 scalar_t__ UDP_V4_FLOW ; 
 scalar_t__ UDP_V6_FLOW ; 
 int flow_type_to_traffic_type (scalar_t__) ; 
 int /*<<< orphan*/  kvfree (void*) ; 
 void* kvzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_modify_tirs_hash (struct mlx5e_priv*,void*,int) ; 
 int /*<<< orphan*/  modify_tir_in ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mlx5e_set_rss_hash_opt(struct mlx5e_priv *priv,
				  struct ethtool_rxnfc *nfc)
{
	int inlen = MLX5_ST_SZ_BYTES(modify_tir_in);
	enum mlx5e_traffic_types tt;
	u8 rx_hash_field = 0;
	void *in;

	tt = flow_type_to_traffic_type(nfc->flow_type);
	if (tt == MLX5E_NUM_INDIR_TIRS)
		return -EINVAL;

	/*  RSS does not support anything other than hashing to queues
	 *  on src IP, dest IP, TCP/UDP src port and TCP/UDP dest
	 *  port.
	 */
	if (nfc->flow_type != TCP_V4_FLOW &&
	    nfc->flow_type != TCP_V6_FLOW &&
	    nfc->flow_type != UDP_V4_FLOW &&
	    nfc->flow_type != UDP_V6_FLOW)
		return -EOPNOTSUPP;

	if (nfc->data & ~(RXH_IP_SRC | RXH_IP_DST |
			  RXH_L4_B_0_1 | RXH_L4_B_2_3))
		return -EOPNOTSUPP;

	if (nfc->data & RXH_IP_SRC)
		rx_hash_field |= MLX5_HASH_FIELD_SEL_SRC_IP;
	if (nfc->data & RXH_IP_DST)
		rx_hash_field |= MLX5_HASH_FIELD_SEL_DST_IP;
	if (nfc->data & RXH_L4_B_0_1)
		rx_hash_field |= MLX5_HASH_FIELD_SEL_L4_SPORT;
	if (nfc->data & RXH_L4_B_2_3)
		rx_hash_field |= MLX5_HASH_FIELD_SEL_L4_DPORT;

	in = kvzalloc(inlen, GFP_KERNEL);
	if (!in)
		return -ENOMEM;

	mutex_lock(&priv->state_lock);

	if (rx_hash_field == priv->rss_params.rx_hash_fields[tt])
		goto out;

	priv->rss_params.rx_hash_fields[tt] = rx_hash_field;
	mlx5e_modify_tirs_hash(priv, in, inlen);

out:
	mutex_unlock(&priv->state_lock);
	kvfree(in);
	return 0;
}