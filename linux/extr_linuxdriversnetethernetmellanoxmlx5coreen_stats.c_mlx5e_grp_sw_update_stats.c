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
struct mlx5e_xdpsq_stats {scalar_t__ cqes; scalar_t__ err; scalar_t__ full; scalar_t__ xmit; } ;
struct mlx5e_sw_stats {int /*<<< orphan*/  tx_cqes; int /*<<< orphan*/  tx_csum_partial; int /*<<< orphan*/  tx_csum_none; int /*<<< orphan*/  tx_csum_partial_inner; int /*<<< orphan*/  tx_xmit_more; int /*<<< orphan*/  tx_recover; int /*<<< orphan*/  tx_cqe_err; int /*<<< orphan*/  tx_queue_dropped; int /*<<< orphan*/  tx_queue_wake; int /*<<< orphan*/  tx_queue_stopped; int /*<<< orphan*/  tx_nop; int /*<<< orphan*/  tx_added_vlan_packets; int /*<<< orphan*/  tx_tso_inner_bytes; int /*<<< orphan*/  tx_tso_inner_packets; int /*<<< orphan*/  tx_tso_bytes; int /*<<< orphan*/  tx_tso_packets; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_xdp_cqes; int /*<<< orphan*/  tx_xdp_err; int /*<<< orphan*/  tx_xdp_full; int /*<<< orphan*/  tx_xdp_xmit; int /*<<< orphan*/  ch_eq_rearm; int /*<<< orphan*/  ch_aff_change; int /*<<< orphan*/  ch_arm; int /*<<< orphan*/  ch_poll; int /*<<< orphan*/  ch_events; int /*<<< orphan*/  rx_congst_umr; int /*<<< orphan*/  rx_cache_waive; int /*<<< orphan*/  rx_cache_busy; int /*<<< orphan*/  rx_cache_empty; int /*<<< orphan*/  rx_cache_full; int /*<<< orphan*/  rx_cache_reuse; int /*<<< orphan*/  rx_page_reuse; int /*<<< orphan*/  rx_cqe_compress_pkts; int /*<<< orphan*/  rx_cqe_compress_blks; int /*<<< orphan*/  rx_buff_alloc_err; int /*<<< orphan*/  rx_oversize_pkts_sw_drop; int /*<<< orphan*/  rx_mpwqe_filler_strides; int /*<<< orphan*/  rx_mpwqe_filler_cqes; int /*<<< orphan*/  rx_wqe_err; int /*<<< orphan*/  rx_xdp_tx_cqe; int /*<<< orphan*/  rx_xdp_tx_err; int /*<<< orphan*/  rx_xdp_tx_full; int /*<<< orphan*/  rx_xdp_tx_xmit; int /*<<< orphan*/  rx_xdp_redirect; int /*<<< orphan*/  rx_xdp_drop; int /*<<< orphan*/  rx_csum_unnecessary_inner; int /*<<< orphan*/  rx_csum_unnecessary; int /*<<< orphan*/  rx_csum_complete; int /*<<< orphan*/  rx_csum_none; int /*<<< orphan*/  rx_removed_vlan_packets; int /*<<< orphan*/  rx_lro_bytes; int /*<<< orphan*/  rx_lro_packets; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct mlx5e_sq_stats {scalar_t__ cqes; scalar_t__ csum_partial; scalar_t__ csum_none; scalar_t__ csum_partial_inner; scalar_t__ xmit_more; scalar_t__ recover; scalar_t__ cqe_err; scalar_t__ dropped; scalar_t__ wake; scalar_t__ stopped; scalar_t__ nop; scalar_t__ added_vlan_packets; scalar_t__ tso_inner_bytes; scalar_t__ tso_inner_packets; scalar_t__ tso_bytes; scalar_t__ tso_packets; scalar_t__ bytes; scalar_t__ packets; } ;
struct mlx5e_rq_stats {scalar_t__ congst_umr; scalar_t__ cache_waive; scalar_t__ cache_busy; scalar_t__ cache_empty; scalar_t__ cache_full; scalar_t__ cache_reuse; scalar_t__ page_reuse; scalar_t__ cqe_compress_pkts; scalar_t__ cqe_compress_blks; scalar_t__ buff_alloc_err; scalar_t__ oversize_pkts_sw_drop; scalar_t__ mpwqe_filler_strides; scalar_t__ mpwqe_filler_cqes; scalar_t__ wqe_err; scalar_t__ xdp_redirect; scalar_t__ xdp_drop; scalar_t__ csum_unnecessary_inner; scalar_t__ csum_unnecessary; scalar_t__ csum_complete; scalar_t__ csum_none; scalar_t__ removed_vlan_packets; scalar_t__ lro_bytes; scalar_t__ lro_packets; scalar_t__ bytes; scalar_t__ packets; } ;
struct TYPE_3__ {int /*<<< orphan*/  sw; } ;
struct mlx5e_priv {int max_opened_tc; TYPE_1__ stats; struct mlx5e_channel_stats* channel_stats; int /*<<< orphan*/  mdev; TYPE_2__* profile; } ;
struct mlx5e_ch_stats {scalar_t__ eq_rearm; scalar_t__ aff_change; scalar_t__ arm; scalar_t__ poll; scalar_t__ events; } ;
struct mlx5e_channel_stats {struct mlx5e_sq_stats* sq; struct mlx5e_ch_stats ch; struct mlx5e_rq_stats rq; struct mlx5e_xdpsq_stats rq_xdpsq; struct mlx5e_xdpsq_stats xdpsq; } ;
struct TYPE_4__ {int (* max_nch ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct mlx5e_sw_stats*,int) ; 
 int /*<<< orphan*/  memset (struct mlx5e_sw_stats*,int /*<<< orphan*/ ,int) ; 
 int stub1 (int /*<<< orphan*/ ) ; 

void mlx5e_grp_sw_update_stats(struct mlx5e_priv *priv)
{
	struct mlx5e_sw_stats temp, *s = &temp;
	int i;

	memset(s, 0, sizeof(*s));

	for (i = 0; i < priv->profile->max_nch(priv->mdev); i++) {
		struct mlx5e_channel_stats *channel_stats =
			&priv->channel_stats[i];
		struct mlx5e_xdpsq_stats *xdpsq_red_stats = &channel_stats->xdpsq;
		struct mlx5e_xdpsq_stats *xdpsq_stats = &channel_stats->rq_xdpsq;
		struct mlx5e_rq_stats *rq_stats = &channel_stats->rq;
		struct mlx5e_ch_stats *ch_stats = &channel_stats->ch;
		int j;

		s->rx_packets	+= rq_stats->packets;
		s->rx_bytes	+= rq_stats->bytes;
		s->rx_lro_packets += rq_stats->lro_packets;
		s->rx_lro_bytes	+= rq_stats->lro_bytes;
		s->rx_removed_vlan_packets += rq_stats->removed_vlan_packets;
		s->rx_csum_none	+= rq_stats->csum_none;
		s->rx_csum_complete += rq_stats->csum_complete;
		s->rx_csum_unnecessary += rq_stats->csum_unnecessary;
		s->rx_csum_unnecessary_inner += rq_stats->csum_unnecessary_inner;
		s->rx_xdp_drop     += rq_stats->xdp_drop;
		s->rx_xdp_redirect += rq_stats->xdp_redirect;
		s->rx_xdp_tx_xmit  += xdpsq_stats->xmit;
		s->rx_xdp_tx_full  += xdpsq_stats->full;
		s->rx_xdp_tx_err   += xdpsq_stats->err;
		s->rx_xdp_tx_cqe   += xdpsq_stats->cqes;
		s->rx_wqe_err   += rq_stats->wqe_err;
		s->rx_mpwqe_filler_cqes    += rq_stats->mpwqe_filler_cqes;
		s->rx_mpwqe_filler_strides += rq_stats->mpwqe_filler_strides;
		s->rx_oversize_pkts_sw_drop += rq_stats->oversize_pkts_sw_drop;
		s->rx_buff_alloc_err += rq_stats->buff_alloc_err;
		s->rx_cqe_compress_blks += rq_stats->cqe_compress_blks;
		s->rx_cqe_compress_pkts += rq_stats->cqe_compress_pkts;
		s->rx_page_reuse  += rq_stats->page_reuse;
		s->rx_cache_reuse += rq_stats->cache_reuse;
		s->rx_cache_full  += rq_stats->cache_full;
		s->rx_cache_empty += rq_stats->cache_empty;
		s->rx_cache_busy  += rq_stats->cache_busy;
		s->rx_cache_waive += rq_stats->cache_waive;
		s->rx_congst_umr  += rq_stats->congst_umr;
		s->ch_events      += ch_stats->events;
		s->ch_poll        += ch_stats->poll;
		s->ch_arm         += ch_stats->arm;
		s->ch_aff_change  += ch_stats->aff_change;
		s->ch_eq_rearm    += ch_stats->eq_rearm;
		/* xdp redirect */
		s->tx_xdp_xmit    += xdpsq_red_stats->xmit;
		s->tx_xdp_full    += xdpsq_red_stats->full;
		s->tx_xdp_err     += xdpsq_red_stats->err;
		s->tx_xdp_cqes    += xdpsq_red_stats->cqes;

		for (j = 0; j < priv->max_opened_tc; j++) {
			struct mlx5e_sq_stats *sq_stats = &channel_stats->sq[j];

			s->tx_packets		+= sq_stats->packets;
			s->tx_bytes		+= sq_stats->bytes;
			s->tx_tso_packets	+= sq_stats->tso_packets;
			s->tx_tso_bytes		+= sq_stats->tso_bytes;
			s->tx_tso_inner_packets	+= sq_stats->tso_inner_packets;
			s->tx_tso_inner_bytes	+= sq_stats->tso_inner_bytes;
			s->tx_added_vlan_packets += sq_stats->added_vlan_packets;
			s->tx_nop               += sq_stats->nop;
			s->tx_queue_stopped	+= sq_stats->stopped;
			s->tx_queue_wake	+= sq_stats->wake;
			s->tx_queue_dropped	+= sq_stats->dropped;
			s->tx_cqe_err		+= sq_stats->cqe_err;
			s->tx_recover		+= sq_stats->recover;
			s->tx_xmit_more		+= sq_stats->xmit_more;
			s->tx_csum_partial_inner += sq_stats->csum_partial_inner;
			s->tx_csum_none		+= sq_stats->csum_none;
			s->tx_csum_partial	+= sq_stats->csum_partial;
#ifdef CONFIG_MLX5_EN_TLS
			s->tx_tls_ooo		+= sq_stats->tls_ooo;
			s->tx_tls_resync_bytes	+= sq_stats->tls_resync_bytes;
#endif
			s->tx_cqes		+= sq_stats->cqes;
		}
	}

	memcpy(&priv->stats.sw, s, sizeof(*s));
}