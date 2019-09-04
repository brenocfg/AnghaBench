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
typedef  int u8 ;
typedef  int u32 ;

/* Variables and functions */
 int BYTES_IN_DWORD ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u32 qed_dump_align(char *dump_buf, bool dump, u32 byte_offset)
{
	u8 offset_in_dword, align_size;

	offset_in_dword = (u8)(byte_offset & 0x3);
	align_size = offset_in_dword ? BYTES_IN_DWORD - offset_in_dword : 0;

	if (dump && align_size)
		memset(dump_buf, 0, align_size);

	return align_size;
}