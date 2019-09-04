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
struct TYPE_7__ {void* buf; } ;
struct TYPE_8__ {TYPE_3__ mask_id_free_list; void* last_used; scalar_t__ init_unallocated; } ;
struct TYPE_5__ {int /*<<< orphan*/  buf; } ;
struct TYPE_6__ {int /*<<< orphan*/  init_unalloc; TYPE_1__ free_list; } ;
struct nfp_flower_priv {TYPE_4__ mask_ids; TYPE_2__ stats_ids; int /*<<< orphan*/  mask_id_seed; int /*<<< orphan*/  flow_table; int /*<<< orphan*/  mask_table; } ;
struct nfp_app {struct nfp_flower_priv* priv; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int NFP_FLOWER_MASK_ELEMENT_RS ; 
 scalar_t__ NFP_FLOWER_MASK_ENTRY_RS ; 
 int /*<<< orphan*/  NFP_FL_REPEATED_HASH_MAX ; 
 int /*<<< orphan*/  NFP_FL_STATS_ELEM_RS ; 
 int /*<<< orphan*/  NFP_FL_STATS_ENTRY_RS ; 
 int /*<<< orphan*/  array_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_random_bytes (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hash_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmalloc_array (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmalloc (int /*<<< orphan*/ ) ; 

int nfp_flower_metadata_init(struct nfp_app *app)
{
	struct nfp_flower_priv *priv = app->priv;

	hash_init(priv->mask_table);
	hash_init(priv->flow_table);
	get_random_bytes(&priv->mask_id_seed, sizeof(priv->mask_id_seed));

	/* Init ring buffer and unallocated mask_ids. */
	priv->mask_ids.mask_id_free_list.buf =
		kmalloc_array(NFP_FLOWER_MASK_ENTRY_RS,
			      NFP_FLOWER_MASK_ELEMENT_RS, GFP_KERNEL);
	if (!priv->mask_ids.mask_id_free_list.buf)
		return -ENOMEM;

	priv->mask_ids.init_unallocated = NFP_FLOWER_MASK_ENTRY_RS - 1;

	/* Init timestamps for mask id*/
	priv->mask_ids.last_used =
		kmalloc_array(NFP_FLOWER_MASK_ENTRY_RS,
			      sizeof(*priv->mask_ids.last_used), GFP_KERNEL);
	if (!priv->mask_ids.last_used)
		goto err_free_mask_id;

	/* Init ring buffer and unallocated stats_ids. */
	priv->stats_ids.free_list.buf =
		vmalloc(array_size(NFP_FL_STATS_ELEM_RS,
				   NFP_FL_STATS_ENTRY_RS));
	if (!priv->stats_ids.free_list.buf)
		goto err_free_last_used;

	priv->stats_ids.init_unalloc = NFP_FL_REPEATED_HASH_MAX;

	return 0;

err_free_last_used:
	kfree(priv->mask_ids.last_used);
err_free_mask_id:
	kfree(priv->mask_ids.mask_id_free_list.buf);
	return -ENOMEM;
}