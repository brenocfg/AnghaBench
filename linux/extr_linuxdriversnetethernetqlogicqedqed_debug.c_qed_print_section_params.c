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

/* Variables and functions */
 int /*<<< orphan*/  qed_get_buf_ptr (char*,scalar_t__) ; 
 scalar_t__ qed_read_param (scalar_t__*,char const**,char const**,scalar_t__*) ; 
 scalar_t__ sprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static u32 qed_print_section_params(u32 *dump_buf,
				    u32 num_section_params,
				    char *results_buf, u32 *num_chars_printed)
{
	u32 i, dump_offset = 0, results_offset = 0;

	for (i = 0; i < num_section_params; i++) {
		const char *param_name, *param_str_val;
		u32 param_num_val = 0;

		dump_offset += qed_read_param(dump_buf + dump_offset,
					      &param_name,
					      &param_str_val, &param_num_val);

		if (param_str_val)
			results_offset +=
				sprintf(qed_get_buf_ptr(results_buf,
							results_offset),
					"%s: %s\n", param_name, param_str_val);
		else if (strcmp(param_name, "fw-timestamp"))
			results_offset +=
				sprintf(qed_get_buf_ptr(results_buf,
							results_offset),
					"%s: %d\n", param_name, param_num_val);
	}

	results_offset += sprintf(qed_get_buf_ptr(results_buf, results_offset),
				  "\n");

	*num_chars_printed = results_offset;

	return dump_offset;
}