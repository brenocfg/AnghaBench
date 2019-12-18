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
struct mlx4_ib_rss {int base_qpn_tbl_sz; int flags; int /*<<< orphan*/  rss_key; } ;
struct mlx4_ib_dev {TYPE_4__* dev; } ;
struct mlx4_ib_create_qp_rss {scalar_t__ rx_hash_function; int rx_hash_fields_mask; int /*<<< orphan*/  rx_hash_key; } ;
struct ib_qp_init_attr {TYPE_2__* rwq_ind_tbl; } ;
struct TYPE_7__ {int flags2; int flags; scalar_t__ tunnel_offload_mode; } ;
struct TYPE_8__ {TYPE_3__ caps; } ;
struct TYPE_6__ {int log_ind_tbl_size; TYPE_1__** ind_tbl; } ;
struct TYPE_5__ {int wq_num; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int MLX4_DEV_CAP_FLAG2_RSS_TOP ; 
 int MLX4_DEV_CAP_FLAG_UDP_RSS ; 
 int /*<<< orphan*/  MLX4_EN_RSS_KEY_SIZE ; 
 int MLX4_IB_RX_HASH_DST_IPV4 ; 
 int MLX4_IB_RX_HASH_DST_IPV6 ; 
 int MLX4_IB_RX_HASH_DST_PORT_TCP ; 
 int MLX4_IB_RX_HASH_DST_PORT_UDP ; 
 scalar_t__ MLX4_IB_RX_HASH_FUNC_TOEPLITZ ; 
 int MLX4_IB_RX_HASH_INNER ; 
 int MLX4_IB_RX_HASH_SRC_IPV4 ; 
 int MLX4_IB_RX_HASH_SRC_IPV6 ; 
 int MLX4_IB_RX_HASH_SRC_PORT_TCP ; 
 int MLX4_IB_RX_HASH_SRC_PORT_UDP ; 
 int MLX4_RSS_BY_INNER_HEADERS_IPONLY ; 
 int MLX4_RSS_IPV4 ; 
 int MLX4_RSS_IPV6 ; 
 int MLX4_RSS_TCP_IPV4 ; 
 int MLX4_RSS_TCP_IPV6 ; 
 int MLX4_RSS_UDP_IPV4 ; 
 int MLX4_RSS_UDP_IPV6 ; 
 scalar_t__ MLX4_TUNNEL_OFFLOAD_MODE_VXLAN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 

__attribute__((used)) static int set_qp_rss(struct mlx4_ib_dev *dev, struct mlx4_ib_rss *rss_ctx,
		      struct ib_qp_init_attr *init_attr,
		      struct mlx4_ib_create_qp_rss *ucmd)
{
	rss_ctx->base_qpn_tbl_sz = init_attr->rwq_ind_tbl->ind_tbl[0]->wq_num |
		(init_attr->rwq_ind_tbl->log_ind_tbl_size << 24);

	if ((ucmd->rx_hash_function == MLX4_IB_RX_HASH_FUNC_TOEPLITZ) &&
	    (dev->dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_RSS_TOP)) {
		memcpy(rss_ctx->rss_key, ucmd->rx_hash_key,
		       MLX4_EN_RSS_KEY_SIZE);
	} else {
		pr_debug("RX Hash function is not supported\n");
		return (-EOPNOTSUPP);
	}

	if (ucmd->rx_hash_fields_mask & ~(MLX4_IB_RX_HASH_SRC_IPV4	|
					  MLX4_IB_RX_HASH_DST_IPV4	|
					  MLX4_IB_RX_HASH_SRC_IPV6	|
					  MLX4_IB_RX_HASH_DST_IPV6	|
					  MLX4_IB_RX_HASH_SRC_PORT_TCP	|
					  MLX4_IB_RX_HASH_DST_PORT_TCP	|
					  MLX4_IB_RX_HASH_SRC_PORT_UDP	|
					  MLX4_IB_RX_HASH_DST_PORT_UDP  |
					  MLX4_IB_RX_HASH_INNER)) {
		pr_debug("RX Hash fields_mask has unsupported mask (0x%llx)\n",
			 ucmd->rx_hash_fields_mask);
		return (-EOPNOTSUPP);
	}

	if ((ucmd->rx_hash_fields_mask & MLX4_IB_RX_HASH_SRC_IPV4) &&
	    (ucmd->rx_hash_fields_mask & MLX4_IB_RX_HASH_DST_IPV4)) {
		rss_ctx->flags = MLX4_RSS_IPV4;
	} else if ((ucmd->rx_hash_fields_mask & MLX4_IB_RX_HASH_SRC_IPV4) ||
		   (ucmd->rx_hash_fields_mask & MLX4_IB_RX_HASH_DST_IPV4)) {
		pr_debug("RX Hash fields_mask is not supported - both IPv4 SRC and DST must be set\n");
		return (-EOPNOTSUPP);
	}

	if ((ucmd->rx_hash_fields_mask & MLX4_IB_RX_HASH_SRC_IPV6) &&
	    (ucmd->rx_hash_fields_mask & MLX4_IB_RX_HASH_DST_IPV6)) {
		rss_ctx->flags |= MLX4_RSS_IPV6;
	} else if ((ucmd->rx_hash_fields_mask & MLX4_IB_RX_HASH_SRC_IPV6) ||
		   (ucmd->rx_hash_fields_mask & MLX4_IB_RX_HASH_DST_IPV6)) {
		pr_debug("RX Hash fields_mask is not supported - both IPv6 SRC and DST must be set\n");
		return (-EOPNOTSUPP);
	}

	if ((ucmd->rx_hash_fields_mask & MLX4_IB_RX_HASH_SRC_PORT_UDP) &&
	    (ucmd->rx_hash_fields_mask & MLX4_IB_RX_HASH_DST_PORT_UDP)) {
		if (!(dev->dev->caps.flags & MLX4_DEV_CAP_FLAG_UDP_RSS)) {
			pr_debug("RX Hash fields_mask for UDP is not supported\n");
			return (-EOPNOTSUPP);
		}

		if (rss_ctx->flags & MLX4_RSS_IPV4)
			rss_ctx->flags |= MLX4_RSS_UDP_IPV4;
		if (rss_ctx->flags & MLX4_RSS_IPV6)
			rss_ctx->flags |= MLX4_RSS_UDP_IPV6;
		if (!(rss_ctx->flags & (MLX4_RSS_IPV6 | MLX4_RSS_IPV4))) {
			pr_debug("RX Hash fields_mask is not supported - UDP must be set with IPv4 or IPv6\n");
			return (-EOPNOTSUPP);
		}
	} else if ((ucmd->rx_hash_fields_mask & MLX4_IB_RX_HASH_SRC_PORT_UDP) ||
		   (ucmd->rx_hash_fields_mask & MLX4_IB_RX_HASH_DST_PORT_UDP)) {
		pr_debug("RX Hash fields_mask is not supported - both UDP SRC and DST must be set\n");
		return (-EOPNOTSUPP);
	}

	if ((ucmd->rx_hash_fields_mask & MLX4_IB_RX_HASH_SRC_PORT_TCP) &&
	    (ucmd->rx_hash_fields_mask & MLX4_IB_RX_HASH_DST_PORT_TCP)) {
		if (rss_ctx->flags & MLX4_RSS_IPV4)
			rss_ctx->flags |= MLX4_RSS_TCP_IPV4;
		if (rss_ctx->flags & MLX4_RSS_IPV6)
			rss_ctx->flags |= MLX4_RSS_TCP_IPV6;
		if (!(rss_ctx->flags & (MLX4_RSS_IPV6 | MLX4_RSS_IPV4))) {
			pr_debug("RX Hash fields_mask is not supported - TCP must be set with IPv4 or IPv6\n");
			return (-EOPNOTSUPP);
		}
	} else if ((ucmd->rx_hash_fields_mask & MLX4_IB_RX_HASH_SRC_PORT_TCP) ||
		   (ucmd->rx_hash_fields_mask & MLX4_IB_RX_HASH_DST_PORT_TCP)) {
		pr_debug("RX Hash fields_mask is not supported - both TCP SRC and DST must be set\n");
		return (-EOPNOTSUPP);
	}

	if (ucmd->rx_hash_fields_mask & MLX4_IB_RX_HASH_INNER) {
		if (dev->dev->caps.tunnel_offload_mode ==
		    MLX4_TUNNEL_OFFLOAD_MODE_VXLAN) {
			/*
			 * Hash according to inner headers if exist, otherwise
			 * according to outer headers.
			 */
			rss_ctx->flags |= MLX4_RSS_BY_INNER_HEADERS_IPONLY;
		} else {
			pr_debug("RSS Hash for inner headers isn't supported\n");
			return (-EOPNOTSUPP);
		}
	}

	return 0;
}