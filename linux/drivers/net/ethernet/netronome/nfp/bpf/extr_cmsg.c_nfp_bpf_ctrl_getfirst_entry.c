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
 int /*<<< orphan*/  NFP_CCM_TYPE_BPF_MAP_GETFIRST ; 
 int nfp_bpf_ctrl_entry_op (struct bpf_offloaded_map*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 

int nfp_bpf_ctrl_getfirst_entry(struct bpf_offloaded_map *offmap,
				void *next_key)
{
	return nfp_bpf_ctrl_entry_op(offmap, NFP_CCM_TYPE_BPF_MAP_GETFIRST,
				     NULL, NULL, 0, next_key, NULL);
}