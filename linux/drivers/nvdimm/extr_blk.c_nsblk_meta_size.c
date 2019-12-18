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
struct nd_namespace_blk {int lbasize; } ;

/* Variables and functions */

__attribute__((used)) static u32 nsblk_meta_size(struct nd_namespace_blk *nsblk)
{
	return nsblk->lbasize - ((nsblk->lbasize >= 4096) ? 4096 : 512);
}