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
struct nfp_bpf_map {int /*<<< orphan*/  l; int /*<<< orphan*/  cache_blockers; int /*<<< orphan*/  cache; } ;
struct nfp_app_bpf {int /*<<< orphan*/  maps_in_use; int /*<<< orphan*/  map_elems_in_use; } ;
struct TYPE_2__ {scalar_t__ max_entries; } ;
struct bpf_offloaded_map {TYPE_1__ map; struct nfp_bpf_map* dev_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_consume_skb_any (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nfp_bpf_map*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfp_bpf_ctrl_free_map (struct nfp_app_bpf*,struct nfp_bpf_map*) ; 

__attribute__((used)) static int
nfp_bpf_map_free(struct nfp_app_bpf *bpf, struct bpf_offloaded_map *offmap)
{
	struct nfp_bpf_map *nfp_map = offmap->dev_priv;

	nfp_bpf_ctrl_free_map(bpf, nfp_map);
	dev_consume_skb_any(nfp_map->cache);
	WARN_ON_ONCE(nfp_map->cache_blockers);
	list_del_init(&nfp_map->l);
	bpf->map_elems_in_use -= offmap->map.max_entries;
	bpf->maps_in_use--;
	kfree(nfp_map);

	return 0;
}