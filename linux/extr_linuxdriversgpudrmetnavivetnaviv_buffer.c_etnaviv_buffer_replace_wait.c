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
struct etnaviv_cmdbuf {int /*<<< orphan*/ * vaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  mb () ; 

__attribute__((used)) static void etnaviv_buffer_replace_wait(struct etnaviv_cmdbuf *buffer,
	unsigned int wl_offset, u32 cmd, u32 arg)
{
	u32 *lw = buffer->vaddr + wl_offset;

	lw[1] = arg;
	mb();
	lw[0] = cmd;
	mb();
}