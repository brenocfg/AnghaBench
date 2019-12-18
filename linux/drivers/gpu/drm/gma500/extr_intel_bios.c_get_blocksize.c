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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */

__attribute__((used)) static u16
get_blocksize(void *p)
{
	u16 *block_ptr, block_size;

	block_ptr = (u16 *)((char *)p - 2);
	block_size = *block_ptr;
	return block_size;
}