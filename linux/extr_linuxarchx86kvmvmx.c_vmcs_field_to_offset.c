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

/* Variables and functions */
 size_t ARRAY_SIZE (unsigned short*) ; 
 short ENOENT ; 
 unsigned int ROL16 (unsigned long,int) ; 
 unsigned int array_index_nospec (unsigned int,size_t const) ; 
 unsigned short* vmcs_field_to_offset_table ; 

__attribute__((used)) static inline short vmcs_field_to_offset(unsigned long field)
{
	const size_t size = ARRAY_SIZE(vmcs_field_to_offset_table);
	unsigned short offset;
	unsigned index;

	if (field >> 15)
		return -ENOENT;

	index = ROL16(field, 6);
	if (index >= size)
		return -ENOENT;

	index = array_index_nospec(index, size);
	offset = vmcs_field_to_offset_table[index];
	if (offset == 0)
		return -ENOENT;
	return offset;
}