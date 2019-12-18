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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  put_unaligned_be32 (int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  put_unaligned_be64 (int,unsigned char*) ; 
 int spc_modesense_blockdesc (unsigned char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int spc_modesense_long_blockdesc(unsigned char *buf, u64 blocks, u32 block_size)
{
	if (blocks <= 0xffffffff)
		return spc_modesense_blockdesc(buf + 3, blocks, block_size) + 3;

	*buf++ = 1;		/* LONGLBA */
	buf += 2;
	*buf++ = 16;
	put_unaligned_be64(blocks, buf);
	buf += 12;
	put_unaligned_be32(block_size, buf);

	return 17;
}