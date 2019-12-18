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
typedef  int u32 ;
struct circ_buf {size_t head; size_t tail; int* buf; } ;
struct TYPE_2__ {scalar_t__ init_unalloc; struct circ_buf free_list; } ;
struct nfp_flower_priv {int stats_ring_size; scalar_t__ active_mem_unit; scalar_t__ total_mem_units; TYPE_1__ stats_ids; } ;
struct nfp_app {struct nfp_flower_priv* priv; } ;

/* Variables and functions */
 int ENOENT ; 
 int FIELD_PREP (int /*<<< orphan*/ ,scalar_t__) ; 
 int NFP_FL_STATS_ELEM_RS ; 
 int /*<<< orphan*/  NFP_FL_STAT_ID_MU_NUM ; 
 int /*<<< orphan*/  NFP_FL_STAT_ID_STAT ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 

__attribute__((used)) static int nfp_get_stats_entry(struct nfp_app *app, u32 *stats_context_id)
{
	struct nfp_flower_priv *priv = app->priv;
	u32 freed_stats_id, temp_stats_id;
	struct circ_buf *ring;

	ring = &priv->stats_ids.free_list;
	freed_stats_id = priv->stats_ring_size;
	/* Check for unallocated entries first. */
	if (priv->stats_ids.init_unalloc > 0) {
		if (priv->active_mem_unit == priv->total_mem_units) {
			priv->stats_ids.init_unalloc--;
			priv->active_mem_unit = 0;
		}

		*stats_context_id =
			FIELD_PREP(NFP_FL_STAT_ID_STAT,
				   priv->stats_ids.init_unalloc - 1) |
			FIELD_PREP(NFP_FL_STAT_ID_MU_NUM,
				   priv->active_mem_unit);
		priv->active_mem_unit++;
		return 0;
	}

	/* Check if buffer is empty. */
	if (ring->head == ring->tail) {
		*stats_context_id = freed_stats_id;
		return -ENOENT;
	}

	memcpy(&temp_stats_id, &ring->buf[ring->tail], NFP_FL_STATS_ELEM_RS);
	*stats_context_id = temp_stats_id;
	memcpy(&ring->buf[ring->tail], &freed_stats_id, NFP_FL_STATS_ELEM_RS);
	ring->tail = (ring->tail + NFP_FL_STATS_ELEM_RS) %
		     (priv->stats_ring_size * NFP_FL_STATS_ELEM_RS);

	return 0;
}