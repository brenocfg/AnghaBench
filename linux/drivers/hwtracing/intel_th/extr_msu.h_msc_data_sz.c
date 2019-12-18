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
struct msc_block_desc {int valid_dw; } ;

/* Variables and functions */
 unsigned long MSC_BDESC ; 

__attribute__((used)) static inline unsigned long msc_data_sz(struct msc_block_desc *bdesc)
{
	if (!bdesc->valid_dw)
		return 0;

	return bdesc->valid_dw * 4 - MSC_BDESC;
}