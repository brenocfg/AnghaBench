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
struct msc_block_desc {int hw_tag; } ;

/* Variables and functions */
 int MSC_HW_TAG_BLOCKWRAP ; 

__attribute__((used)) static inline bool msc_block_wrapped(struct msc_block_desc *bdesc)
{
	if (bdesc->hw_tag & MSC_HW_TAG_BLOCKWRAP)
		return true;

	return false;
}