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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  qed_read_param (int /*<<< orphan*/ *,char const**,char const**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 qed_read_section_hdr(u32 *dump_buf,
				const char **section_name,
				u32 *num_section_params)
{
	const char *param_str_val;

	return qed_read_param(dump_buf,
			      section_name, &param_str_val, num_section_params);
}