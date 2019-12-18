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
 int MSC_HW_TAG_ENDBIT ; 
 scalar_t__ msc_block_sz (struct msc_block_desc*) ; 
 scalar_t__ msc_data_sz (struct msc_block_desc*) ; 

__attribute__((used)) static inline bool msc_block_last_written(struct msc_block_desc *bdesc)
{
	if ((bdesc->hw_tag & MSC_HW_TAG_ENDBIT) ||
	    (msc_data_sz(bdesc) != msc_block_sz(bdesc)))
		return true;

	return false;
}