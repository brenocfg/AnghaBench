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
struct pvr2_channel {unsigned int input_mask; } ;

/* Variables and functions */

unsigned int pvr2_channel_get_limited_inputs(struct pvr2_channel *cp)
{
	return cp->input_mask;
}