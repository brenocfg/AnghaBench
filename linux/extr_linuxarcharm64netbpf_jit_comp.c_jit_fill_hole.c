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
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  AARCH64_BREAK_FAULT ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void jit_fill_hole(void *area, unsigned int size)
{
	__le32 *ptr;
	/* We are guaranteed to have aligned memory. */
	for (ptr = area; size >= sizeof(u32); size -= sizeof(u32))
		*ptr++ = cpu_to_le32(AARCH64_BREAK_FAULT);
}