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
struct circ_buf {size_t head; size_t tail; size_t* buf; } ;
struct TYPE_2__ {scalar_t__ init_unallocated; int /*<<< orphan*/ * last_used; struct circ_buf mask_id_free_list; } ;
struct nfp_flower_priv {TYPE_1__ mask_ids; } ;
struct nfp_app {struct nfp_flower_priv* priv; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int ENOENT ; 
 int NFP_FLOWER_MASK_ELEMENT_RS ; 
 int NFP_FLOWER_MASK_ENTRY_RS ; 
 int /*<<< orphan*/  NFP_FL_MASK_REUSE_TIME_NS ; 
 int /*<<< orphan*/  ktime_add_ns (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ktime_before (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  memcpy (size_t*,size_t*,int) ; 

__attribute__((used)) static int nfp_mask_alloc(struct nfp_app *app, u8 *mask_id)
{
	struct nfp_flower_priv *priv = app->priv;
	ktime_t reuse_timeout;
	struct circ_buf *ring;
	u8 temp_id, freed_id;

	ring = &priv->mask_ids.mask_id_free_list;
	freed_id = NFP_FLOWER_MASK_ENTRY_RS - 1;
	/* Checking for unallocated entries first. */
	if (priv->mask_ids.init_unallocated > 0) {
		*mask_id = priv->mask_ids.init_unallocated;
		priv->mask_ids.init_unallocated--;
		return 0;
	}

	/* Checking if buffer is empty. */
	if (ring->head == ring->tail)
		goto err_not_found;

	memcpy(&temp_id, &ring->buf[ring->tail], NFP_FLOWER_MASK_ELEMENT_RS);
	*mask_id = temp_id;

	reuse_timeout = ktime_add_ns(priv->mask_ids.last_used[*mask_id],
				     NFP_FL_MASK_REUSE_TIME_NS);

	if (ktime_before(ktime_get(), reuse_timeout))
		goto err_not_found;

	memcpy(&ring->buf[ring->tail], &freed_id, NFP_FLOWER_MASK_ELEMENT_RS);
	ring->tail = (ring->tail + NFP_FLOWER_MASK_ELEMENT_RS) %
		     (NFP_FLOWER_MASK_ENTRY_RS * NFP_FLOWER_MASK_ELEMENT_RS);

	return 0;

err_not_found:
	*mask_id = freed_id;
	return -ENOENT;
}