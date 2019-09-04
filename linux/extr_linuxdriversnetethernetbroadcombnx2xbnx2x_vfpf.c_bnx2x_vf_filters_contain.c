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
typedef  int u32 ;
struct vfpf_set_q_filters_tlv {int n_mac_vlan_filters; TYPE_1__* filters; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */

__attribute__((used)) static int bnx2x_vf_filters_contain(struct vfpf_set_q_filters_tlv *filters,
				    u32 flags)
{
	int i, cnt = 0;

	for (i = 0; i < filters->n_mac_vlan_filters; i++)
		if  ((filters->filters[i].flags & flags) == flags)
			cnt++;

	return cnt;
}