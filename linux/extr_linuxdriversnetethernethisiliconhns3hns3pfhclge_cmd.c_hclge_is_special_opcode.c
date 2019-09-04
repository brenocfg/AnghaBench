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
 scalar_t__ HCLGE_OPC_STATS_32_BIT ; 
 scalar_t__ HCLGE_OPC_STATS_64_BIT ; 
 scalar_t__ HCLGE_OPC_STATS_MAC ; 

__attribute__((used)) static bool hclge_is_special_opcode(u16 opcode)
{
	/* these commands have several descriptors,
	 * and use the first one to save opcode and return value
	 */
	u16 spec_opcode[3] = {HCLGE_OPC_STATS_64_BIT,
		HCLGE_OPC_STATS_32_BIT, HCLGE_OPC_STATS_MAC};
	int i;

	for (i = 0; i < ARRAY_SIZE(spec_opcode); i++) {
		if (spec_opcode[i] == opcode)
			return true;
	}

	return false;
}