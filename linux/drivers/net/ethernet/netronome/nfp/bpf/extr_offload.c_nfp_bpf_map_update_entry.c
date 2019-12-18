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
typedef  int /*<<< orphan*/  u64 ;
struct bpf_offloaded_map {int /*<<< orphan*/  dev_priv; } ;

/* Variables and functions */
 int nfp_bpf_ctrl_update_entry (struct bpf_offloaded_map*,void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_map_bpf_byte_swap (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  nfp_map_bpf_byte_swap_record (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int
nfp_bpf_map_update_entry(struct bpf_offloaded_map *offmap,
			 void *key, void *value, u64 flags)
{
	nfp_map_bpf_byte_swap(offmap->dev_priv, value);
	nfp_map_bpf_byte_swap_record(offmap->dev_priv, value);
	return nfp_bpf_ctrl_update_entry(offmap, key, value, flags);
}