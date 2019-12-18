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
typedef  scalar_t__ u16 ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 scalar_t__ HCLGE_OPC_QUERY_32_BIT_REG ; 
 scalar_t__ HCLGE_OPC_QUERY_64_BIT_REG ; 
 scalar_t__ HCLGE_OPC_STATS_32_BIT ; 
 scalar_t__ HCLGE_OPC_STATS_64_BIT ; 
 scalar_t__ HCLGE_OPC_STATS_MAC ; 
 scalar_t__ HCLGE_OPC_STATS_MAC_ALL ; 
 scalar_t__ HCLGE_QUERY_CLEAR_ALL_MPF_MSIX_INT ; 
 scalar_t__ HCLGE_QUERY_CLEAR_ALL_PF_MSIX_INT ; 
 scalar_t__ HCLGE_QUERY_CLEAR_MPF_RAS_INT ; 
 scalar_t__ HCLGE_QUERY_CLEAR_PF_RAS_INT ; 

__attribute__((used)) static bool hclge_is_special_opcode(u16 opcode)
{
	/* these commands have several descriptors,
	 * and use the first one to save opcode and return value
	 */
	u16 spec_opcode[] = {HCLGE_OPC_STATS_64_BIT,
			     HCLGE_OPC_STATS_32_BIT,
			     HCLGE_OPC_STATS_MAC,
			     HCLGE_OPC_STATS_MAC_ALL,
			     HCLGE_OPC_QUERY_32_BIT_REG,
			     HCLGE_OPC_QUERY_64_BIT_REG,
			     HCLGE_QUERY_CLEAR_MPF_RAS_INT,
			     HCLGE_QUERY_CLEAR_PF_RAS_INT,
			     HCLGE_QUERY_CLEAR_ALL_MPF_MSIX_INT,
			     HCLGE_QUERY_CLEAR_ALL_PF_MSIX_INT};
	int i;

	for (i = 0; i < ARRAY_SIZE(spec_opcode); i++) {
		if (spec_opcode[i] == opcode)
			return true;
	}

	return false;
}