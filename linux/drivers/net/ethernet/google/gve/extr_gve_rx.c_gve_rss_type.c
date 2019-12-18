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
typedef  enum pkt_hash_types { ____Placeholder_pkt_hash_types } pkt_hash_types ;
typedef  int __be16 ;

/* Variables and functions */
 int GVE_RXF_IPV4 ; 
 int GVE_RXF_IPV6 ; 
 int GVE_RXF_TCP ; 
 int GVE_RXF_UDP ; 
 int PKT_HASH_TYPE_L2 ; 
 int PKT_HASH_TYPE_L3 ; 
 int PKT_HASH_TYPE_L4 ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static enum pkt_hash_types gve_rss_type(__be16 pkt_flags)
{
	if (likely(pkt_flags & (GVE_RXF_TCP | GVE_RXF_UDP)))
		return PKT_HASH_TYPE_L4;
	if (pkt_flags & (GVE_RXF_IPV4 | GVE_RXF_IPV6))
		return PKT_HASH_TYPE_L3;
	return PKT_HASH_TYPE_L2;
}