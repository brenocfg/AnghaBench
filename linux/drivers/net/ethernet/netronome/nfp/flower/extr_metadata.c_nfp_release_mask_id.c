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
typedef  size_t u8 ;
struct circ_buf {size_t head; int /*<<< orphan*/ * buf; int /*<<< orphan*/  tail; } ;
struct TYPE_2__ {int /*<<< orphan*/ * last_used; struct circ_buf mask_id_free_list; } ;
struct nfp_flower_priv {TYPE_1__ mask_ids; } ;
struct nfp_app {struct nfp_flower_priv* priv; } ;

/* Variables and functions */
 scalar_t__ CIRC_SPACE (size_t,int /*<<< orphan*/ ,int) ; 
 int ENOBUFS ; 
 int NFP_FLOWER_MASK_ELEMENT_RS ; 
 int NFP_FLOWER_MASK_ENTRY_RS ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,size_t*,int) ; 

__attribute__((used)) static int nfp_release_mask_id(struct nfp_app *app, u8 mask_id)
{
	struct nfp_flower_priv *priv = app->priv;
	struct circ_buf *ring;

	ring = &priv->mask_ids.mask_id_free_list;
	/* Checking if buffer is full. */
	if (CIRC_SPACE(ring->head, ring->tail, NFP_FLOWER_MASK_ENTRY_RS) == 0)
		return -ENOBUFS;

	memcpy(&ring->buf[ring->head], &mask_id, NFP_FLOWER_MASK_ELEMENT_RS);
	ring->head = (ring->head + NFP_FLOWER_MASK_ELEMENT_RS) %
		     (NFP_FLOWER_MASK_ENTRY_RS * NFP_FLOWER_MASK_ELEMENT_RS);

	priv->mask_ids.last_used[mask_id] = ktime_get();

	return 0;
}