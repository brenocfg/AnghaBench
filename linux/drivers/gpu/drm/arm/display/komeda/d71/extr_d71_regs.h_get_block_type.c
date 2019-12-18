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
struct block_header {int /*<<< orphan*/  block_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_INFO_BLK_TYPE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 get_block_type(struct block_header *blk)
{
	return BLOCK_INFO_BLK_TYPE(blk->block_info);
}