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
typedef  int /*<<< orphan*/  u32 ;
struct circ_buf {size_t head; int /*<<< orphan*/ * buf; int /*<<< orphan*/  tail; } ;
struct TYPE_2__ {struct circ_buf free_list; } ;
struct nfp_flower_priv {int stats_ring_size; TYPE_1__ stats_ids; } ;
struct nfp_app {struct nfp_flower_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIRC_SPACE (size_t,int /*<<< orphan*/ ,int) ; 
 int ENOBUFS ; 
 int NFP_FL_STATS_ELEM_RS ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int nfp_release_stats_entry(struct nfp_app *app, u32 stats_context_id)
{
	struct nfp_flower_priv *priv = app->priv;
	struct circ_buf *ring;

	ring = &priv->stats_ids.free_list;
	/* Check if buffer is full. */
	if (!CIRC_SPACE(ring->head, ring->tail,
			priv->stats_ring_size * NFP_FL_STATS_ELEM_RS -
			NFP_FL_STATS_ELEM_RS + 1))
		return -ENOBUFS;

	memcpy(&ring->buf[ring->head], &stats_context_id, NFP_FL_STATS_ELEM_RS);
	ring->head = (ring->head + NFP_FL_STATS_ELEM_RS) %
		     (priv->stats_ring_size * NFP_FL_STATS_ELEM_RS);

	return 0;
}