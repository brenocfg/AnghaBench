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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct tstorm_eth_mac_filter_config {int dummy; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 scalar_t__ BAR_TSTRORM_INTMEM ; 
 scalar_t__ TSTORM_MAC_FILTER_CONFIG_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __storm_memset_struct (struct bnx2x*,scalar_t__,size_t,scalar_t__*) ; 

__attribute__((used)) static inline void __storm_memset_mac_filters(struct bnx2x *bp,
			struct tstorm_eth_mac_filter_config *mac_filters,
			u16 pf_id)
{
	size_t size = sizeof(struct tstorm_eth_mac_filter_config);

	u32 addr = BAR_TSTRORM_INTMEM +
			TSTORM_MAC_FILTER_CONFIG_OFFSET(pf_id);

	__storm_memset_struct(bp, addr, size, (u32 *)mac_filters);
}