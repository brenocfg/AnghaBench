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
typedef  int u32 ;
struct ib_port_attr {int port_cap_flags; scalar_t__ ip_gids; } ;

/* Variables and functions */
 int IB_UVERBS_PCF_IP_BASED_GIDS ; 

__attribute__((used)) static u32 make_port_cap_flags(const struct ib_port_attr *attr)
{
	u32 res;

	/* All IBA CapabilityMask bits are passed through here, except bit 26,
	 * which is overridden with IP_BASED_GIDS. This is due to a historical
	 * mistake in the implementation of IP_BASED_GIDS. Otherwise all other
	 * bits match the IBA definition across all kernel versions.
	 */
	res = attr->port_cap_flags & ~(u32)IB_UVERBS_PCF_IP_BASED_GIDS;

	if (attr->ip_gids)
		res |= IB_UVERBS_PCF_IP_BASED_GIDS;

	return res;
}