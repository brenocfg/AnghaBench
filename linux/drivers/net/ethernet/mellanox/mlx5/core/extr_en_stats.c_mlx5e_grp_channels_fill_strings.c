#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_9__ {int ever_used; } ;
struct mlx5e_priv {int max_nch; int max_opened_tc; int** channel_tc2txq; TYPE_1__ xsk; } ;
struct TYPE_16__ {char* format; } ;
struct TYPE_15__ {char* format; } ;
struct TYPE_14__ {char* format; } ;
struct TYPE_13__ {char* format; } ;
struct TYPE_12__ {char* format; } ;
struct TYPE_11__ {char* format; } ;
struct TYPE_10__ {char* format; } ;

/* Variables and functions */
 int ETH_GSTRING_LEN ; 
 int NUM_CH_STATS ; 
 int NUM_RQ_STATS ; 
 int NUM_RQ_XDPSQ_STATS ; 
 int NUM_SQ_STATS ; 
 int NUM_XDPSQ_STATS ; 
 int NUM_XSKRQ_STATS ; 
 int NUM_XSKSQ_STATS ; 
 TYPE_8__* ch_stats_desc ; 
 TYPE_7__* rq_stats_desc ; 
 TYPE_6__* rq_xdpsq_stats_desc ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ *,char*,int) ; 
 TYPE_5__* sq_stats_desc ; 
 TYPE_4__* xdpsq_stats_desc ; 
 TYPE_3__* xskrq_stats_desc ; 
 TYPE_2__* xsksq_stats_desc ; 

__attribute__((used)) static int mlx5e_grp_channels_fill_strings(struct mlx5e_priv *priv, u8 *data,
					   int idx)
{
	bool is_xsk = priv->xsk.ever_used;
	int max_nch = priv->max_nch;
	int i, j, tc;

	for (i = 0; i < max_nch; i++)
		for (j = 0; j < NUM_CH_STATS; j++)
			sprintf(data + (idx++) * ETH_GSTRING_LEN,
				ch_stats_desc[j].format, i);

	for (i = 0; i < max_nch; i++) {
		for (j = 0; j < NUM_RQ_STATS; j++)
			sprintf(data + (idx++) * ETH_GSTRING_LEN,
				rq_stats_desc[j].format, i);
		for (j = 0; j < NUM_XSKRQ_STATS * is_xsk; j++)
			sprintf(data + (idx++) * ETH_GSTRING_LEN,
				xskrq_stats_desc[j].format, i);
		for (j = 0; j < NUM_RQ_XDPSQ_STATS; j++)
			sprintf(data + (idx++) * ETH_GSTRING_LEN,
				rq_xdpsq_stats_desc[j].format, i);
	}

	for (tc = 0; tc < priv->max_opened_tc; tc++)
		for (i = 0; i < max_nch; i++)
			for (j = 0; j < NUM_SQ_STATS; j++)
				sprintf(data + (idx++) * ETH_GSTRING_LEN,
					sq_stats_desc[j].format,
					priv->channel_tc2txq[i][tc]);

	for (i = 0; i < max_nch; i++) {
		for (j = 0; j < NUM_XSKSQ_STATS * is_xsk; j++)
			sprintf(data + (idx++) * ETH_GSTRING_LEN,
				xsksq_stats_desc[j].format, i);
		for (j = 0; j < NUM_XDPSQ_STATS; j++)
			sprintf(data + (idx++) * ETH_GSTRING_LEN,
				xdpsq_stats_desc[j].format, i);
	}

	return idx;
}