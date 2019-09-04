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
struct etnaviv_gpu {int /*<<< orphan*/  dev; } ;
struct etnaviv_cmdbuf {int size; int* vaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_PREFIX_OFFSET ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int*,int,int) ; 
 int etnaviv_cmdbuf_get_va (struct etnaviv_cmdbuf*) ; 
 int /*<<< orphan*/  print_hex_dump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,int*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void etnaviv_buffer_dump(struct etnaviv_gpu *gpu,
	struct etnaviv_cmdbuf *buf, u32 off, u32 len)
{
	u32 size = buf->size;
	u32 *ptr = buf->vaddr + off;

	dev_info(gpu->dev, "virt %p phys 0x%08x free 0x%08x\n",
			ptr, etnaviv_cmdbuf_get_va(buf) + off, size - len * 4 - off);

	print_hex_dump(KERN_INFO, "cmd ", DUMP_PREFIX_OFFSET, 16, 4,
			ptr, len * 4, 0);
}