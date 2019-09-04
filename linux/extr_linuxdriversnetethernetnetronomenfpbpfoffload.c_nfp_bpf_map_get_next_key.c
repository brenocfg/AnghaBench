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
struct bpf_offloaded_map {int dummy; } ;

/* Variables and functions */
 int nfp_bpf_ctrl_getfirst_entry (struct bpf_offloaded_map*,void*) ; 
 int nfp_bpf_ctrl_getnext_entry (struct bpf_offloaded_map*,void*,void*) ; 

__attribute__((used)) static int
nfp_bpf_map_get_next_key(struct bpf_offloaded_map *offmap,
			 void *key, void *next_key)
{
	if (!key)
		return nfp_bpf_ctrl_getfirst_entry(offmap, next_key);
	return nfp_bpf_ctrl_getnext_entry(offmap, key, next_key);
}