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
typedef  size_t u8 ;
typedef  int u32 ;

/* Variables and functions */
 int BITS_PER_COMMAND ; 
 int GROUPS_PER_BIT ; 
 int IR_RC5_MAX_BIT ; 
 size_t IR_RC5_MIN_BIT ; 

__attribute__((used)) static u32 smi_decode_rc5(u8 *pData, u8 size)
{
	u8 index, current_bit, bit_count;
	u8 group_array[BITS_PER_COMMAND * GROUPS_PER_BIT + 4];
	u8 group_index = 0;
	u32 command = 0xFFFFFFFF;

	group_array[group_index++] = 1;

	for (index = 0; index < size; index++) {

		current_bit = (pData[index] & 0x80) ? 1 : 0;
		bit_count = pData[index] & 0x7f;

		if ((current_bit == 1) && (bit_count >= 2*IR_RC5_MAX_BIT + 1)) {
			goto process_code;
		} else if ((bit_count >= IR_RC5_MIN_BIT) &&
			   (bit_count <= IR_RC5_MAX_BIT)) {
				group_array[group_index++] = current_bit;
		} else if ((bit_count > IR_RC5_MAX_BIT) &&
			   (bit_count <= 2*IR_RC5_MAX_BIT)) {
				group_array[group_index++] = current_bit;
				group_array[group_index++] = current_bit;
		} else {
			goto invalid_timing;
		}
		if (group_index >= BITS_PER_COMMAND*GROUPS_PER_BIT)
			goto process_code;

		if ((group_index == BITS_PER_COMMAND*GROUPS_PER_BIT - 1)
		    && (group_array[group_index-1] == 0)) {
			group_array[group_index++] = 1;
			goto process_code;
		}
	}

process_code:
	if (group_index == (BITS_PER_COMMAND*GROUPS_PER_BIT-1))
		group_array[group_index++] = 1;

	if (group_index == BITS_PER_COMMAND*GROUPS_PER_BIT) {
		command = 0;
		for (index = 0; index < (BITS_PER_COMMAND*GROUPS_PER_BIT);
		     index = index + 2) {
			if ((group_array[index] == 1) &&
			    (group_array[index+1] == 0)) {
				command |= (1 << (BITS_PER_COMMAND -
						   (index/2) - 1));
			} else if ((group_array[index] == 0) &&
				   (group_array[index+1] == 1)) {
				/* */
			} else {
				command = 0xFFFFFFFF;
				goto invalid_timing;
			}
		}
	}

invalid_timing:
	return command;
}