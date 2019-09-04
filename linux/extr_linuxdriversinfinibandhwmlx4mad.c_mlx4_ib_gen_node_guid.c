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
typedef  int u64 ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 scalar_t__ IB_OPENIB_OUI ; 
 int /*<<< orphan*/  cpu_to_be64 (int) ; 
 int prandom_u32 () ; 

__be64 mlx4_ib_gen_node_guid(void)
{
#define NODE_GUID_HI	((u64) (((u64)IB_OPENIB_OUI) << 40))
	return cpu_to_be64(NODE_GUID_HI | prandom_u32());
}