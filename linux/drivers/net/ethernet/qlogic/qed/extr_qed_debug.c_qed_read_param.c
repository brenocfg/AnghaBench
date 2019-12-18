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

/* Variables and functions */
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static u32 qed_read_param(u32 *dump_buf,
			  const char **param_name,
			  const char **param_str_val, u32 *param_num_val)
{
	char *char_buf = (char *)dump_buf;
	size_t offset = 0;

	/* Extract param name */
	*param_name = char_buf;
	offset += strlen(*param_name) + 1;

	/* Check param type */
	if (*(char_buf + offset++)) {
		/* String param */
		*param_str_val = char_buf + offset;
		*param_num_val = 0;
		offset += strlen(*param_str_val) + 1;
		if (offset & 0x3)
			offset += (4 - (offset & 0x3));
	} else {
		/* Numeric param */
		*param_str_val = NULL;
		if (offset & 0x3)
			offset += (4 - (offset & 0x3));
		*param_num_val = *(u32 *)(char_buf + offset);
		offset += 4;
	}

	return (u32)offset / 4;
}