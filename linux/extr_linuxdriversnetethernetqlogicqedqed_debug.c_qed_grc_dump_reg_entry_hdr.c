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
 int REG_DUMP_LEN_SHIFT ; 

__attribute__((used)) static u32 qed_grc_dump_reg_entry_hdr(u32 *dump_buf,
				      bool dump, u32 addr, u32 len)
{
	if (dump)
		*dump_buf = addr | (len << REG_DUMP_LEN_SHIFT);

	return 1;
}