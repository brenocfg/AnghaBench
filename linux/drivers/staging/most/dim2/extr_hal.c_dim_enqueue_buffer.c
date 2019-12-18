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
typedef  int /*<<< orphan*/  u16 ;
struct dim_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIM_ERR_DRIVER_NOT_INITIALIZED ; 
 int channel_start (struct dim_channel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dim_on_error (int /*<<< orphan*/ ,char*) ; 

bool dim_enqueue_buffer(struct dim_channel *ch, u32 buffer_addr,
			u16 buffer_size)
{
	if (!ch)
		return dim_on_error(DIM_ERR_DRIVER_NOT_INITIALIZED,
				    "Bad channel");

	return channel_start(ch, buffer_addr, buffer_size);
}