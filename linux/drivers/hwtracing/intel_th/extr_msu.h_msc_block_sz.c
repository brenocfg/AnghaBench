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
struct msc_block_desc {int block_sz; } ;

/* Variables and functions */
 unsigned long MSC_BDESC ; 

__attribute__((used)) static inline unsigned long msc_block_sz(struct msc_block_desc *bdesc)
{
	return bdesc->block_sz * 64 - MSC_BDESC;
}