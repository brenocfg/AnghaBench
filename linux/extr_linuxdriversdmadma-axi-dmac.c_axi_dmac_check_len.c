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
struct axi_dmac_chan {unsigned int max_length; unsigned int align_mask; } ;

/* Variables and functions */

__attribute__((used)) static bool axi_dmac_check_len(struct axi_dmac_chan *chan, unsigned int len)
{
	if (len == 0 || len > chan->max_length)
		return false;
	if ((len & chan->align_mask) != 0) /* Not aligned */
		return false;
	return true;
}