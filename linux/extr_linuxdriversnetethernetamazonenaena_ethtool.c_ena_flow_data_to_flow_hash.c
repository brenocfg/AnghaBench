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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  ENA_ADMIN_RSS_L2_DA ; 
 int /*<<< orphan*/  ENA_ADMIN_RSS_L3_DA ; 
 int /*<<< orphan*/  ENA_ADMIN_RSS_L3_SA ; 
 int /*<<< orphan*/  ENA_ADMIN_RSS_L4_DP ; 
 int /*<<< orphan*/  ENA_ADMIN_RSS_L4_SP ; 
 int RXH_IP_DST ; 
 int RXH_IP_SRC ; 
 int RXH_L2DA ; 
 int RXH_L4_B_0_1 ; 
 int RXH_L4_B_2_3 ; 

__attribute__((used)) static u16 ena_flow_data_to_flow_hash(u32 hash_fields)
{
	u16 data = 0;

	if (hash_fields & RXH_L2DA)
		data |= ENA_ADMIN_RSS_L2_DA;

	if (hash_fields & RXH_IP_DST)
		data |= ENA_ADMIN_RSS_L3_DA;

	if (hash_fields & RXH_IP_SRC)
		data |= ENA_ADMIN_RSS_L3_SA;

	if (hash_fields & RXH_L4_B_2_3)
		data |= ENA_ADMIN_RSS_L4_DP;

	if (hash_fields & RXH_L4_B_0_1)
		data |= ENA_ADMIN_RSS_L4_SP;

	return data;
}