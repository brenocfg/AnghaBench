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
 int /*<<< orphan*/  qed_dump_num_param (int /*<<< orphan*/ *,int,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 qed_dump_section_hdr(u32 *dump_buf,
				bool dump, const char *name, u32 num_params)
{
	return qed_dump_num_param(dump_buf, dump, name, num_params);
}