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
 int BYTES_TO_DWORDS (int) ; 
 int qed_dump_align (char*,int,int) ; 
 int qed_dump_str (char*,int,char const*) ; 

__attribute__((used)) static u32 qed_dump_str_param(u32 *dump_buf,
			      bool dump,
			      const char *param_name, const char *param_val)
{
	char *char_buf = (char *)dump_buf;
	u32 offset = 0;

	/* Dump param name */
	offset += qed_dump_str(char_buf + offset, dump, param_name);

	/* Indicate a string param value */
	if (dump)
		*(char_buf + offset) = 1;
	offset++;

	/* Dump param value */
	offset += qed_dump_str(char_buf + offset, dump, param_val);

	/* Align buffer to next dword */
	offset += qed_dump_align(char_buf + offset, dump, offset);

	return BYTES_TO_DWORDS(offset);
}