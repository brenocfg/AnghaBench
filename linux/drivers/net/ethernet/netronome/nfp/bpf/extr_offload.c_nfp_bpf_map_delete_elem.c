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
struct TYPE_2__ {scalar_t__ map_type; } ;
struct bpf_offloaded_map {TYPE_1__ map; } ;

/* Variables and functions */
 scalar_t__ BPF_MAP_TYPE_ARRAY ; 
 int EINVAL ; 
 int nfp_bpf_ctrl_del_entry (struct bpf_offloaded_map*,void*) ; 

__attribute__((used)) static int
nfp_bpf_map_delete_elem(struct bpf_offloaded_map *offmap, void *key)
{
	if (offmap->map.map_type == BPF_MAP_TYPE_ARRAY)
		return -EINVAL;
	return nfp_bpf_ctrl_del_entry(offmap, key);
}