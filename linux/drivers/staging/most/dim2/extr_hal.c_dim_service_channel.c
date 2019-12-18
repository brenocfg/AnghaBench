#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct dim_channel {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dim_is_initialized; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIM_ERR_DRIVER_NOT_INITIALIZED ; 
 int /*<<< orphan*/  channel_service (struct dim_channel*) ; 
 TYPE_1__ g ; 

u8 dim_service_channel(struct dim_channel *ch)
{
	if (!g.dim_is_initialized || !ch)
		return DIM_ERR_DRIVER_NOT_INITIALIZED;

	return channel_service(ch);
}