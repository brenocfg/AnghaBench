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
typedef  scalar_t__ u16 ;
struct dim_channel {scalar_t__ done_sw_buffers_number; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIM_ERR_UNDERFLOW ; 
 int dim_on_error (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool channel_detach_buffers(struct dim_channel *ch, u16 buffers_number)
{
	if (buffers_number > ch->done_sw_buffers_number)
		return dim_on_error(DIM_ERR_UNDERFLOW, "Channel underflow");

	ch->done_sw_buffers_number -= buffers_number;
	return true;
}