#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct nfp_prog {int /*<<< orphan*/  map_records_cnt; struct nfp_bpf_neutral_map** map_records; } ;
struct nfp_bpf_neutral_map {int count; int /*<<< orphan*/  l; int /*<<< orphan*/  map_id; struct bpf_map* ptr; } ;
struct nfp_app_bpf {int /*<<< orphan*/  maps_neutral; } ;
struct bpf_map {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct bpf_map*) ; 
 int PTR_ERR (struct bpf_map*) ; 
 struct bpf_map* bpf_map_inc (struct bpf_map*,int) ; 
 int /*<<< orphan*/  bpf_map_put (struct bpf_map*) ; 
 int /*<<< orphan*/  kfree (struct nfp_bpf_neutral_map*) ; 
 struct nfp_bpf_neutral_map* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_bpf_maps_neutral_params ; 
 int rhashtable_insert_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct nfp_bpf_neutral_map* rhashtable_lookup_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfp_map_ptr_record(struct nfp_app_bpf *bpf, struct nfp_prog *nfp_prog,
		   struct bpf_map *map)
{
	struct nfp_bpf_neutral_map *record;
	int err;

	/* Reuse path - other offloaded program is already tracking this map. */
	record = rhashtable_lookup_fast(&bpf->maps_neutral, &map->id,
					nfp_bpf_maps_neutral_params);
	if (record) {
		nfp_prog->map_records[nfp_prog->map_records_cnt++] = record;
		record->count++;
		return 0;
	}

	/* Grab a single ref to the map for our record.  The prog destroy ndo
	 * happens after free_used_maps().
	 */
	map = bpf_map_inc(map, false);
	if (IS_ERR(map))
		return PTR_ERR(map);

	record = kmalloc(sizeof(*record), GFP_KERNEL);
	if (!record) {
		err = -ENOMEM;
		goto err_map_put;
	}

	record->ptr = map;
	record->map_id = map->id;
	record->count = 1;

	err = rhashtable_insert_fast(&bpf->maps_neutral, &record->l,
				     nfp_bpf_maps_neutral_params);
	if (err)
		goto err_free_rec;

	nfp_prog->map_records[nfp_prog->map_records_cnt++] = record;

	return 0;

err_free_rec:
	kfree(record);
err_map_put:
	bpf_map_put(map);
	return err;
}