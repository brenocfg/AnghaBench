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
struct ice_qs_cfg {int pf_map_size; int q_count; int* vsi_map; int vsi_map_offset; int /*<<< orphan*/  qs_mutex; int /*<<< orphan*/  pf_map; } ;

/* Variables and functions */
 int ENOMEM ; 
 int bitmap_find_next_zero_area (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_set (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __ice_vsi_get_qs_contig(struct ice_qs_cfg *qs_cfg)
{
	int offset, i;

	mutex_lock(qs_cfg->qs_mutex);
	offset = bitmap_find_next_zero_area(qs_cfg->pf_map, qs_cfg->pf_map_size,
					    0, qs_cfg->q_count, 0);
	if (offset >= qs_cfg->pf_map_size) {
		mutex_unlock(qs_cfg->qs_mutex);
		return -ENOMEM;
	}

	bitmap_set(qs_cfg->pf_map, offset, qs_cfg->q_count);
	for (i = 0; i < qs_cfg->q_count; i++)
		qs_cfg->vsi_map[i + qs_cfg->vsi_map_offset] = i + offset;
	mutex_unlock(qs_cfg->qs_mutex);

	return 0;
}