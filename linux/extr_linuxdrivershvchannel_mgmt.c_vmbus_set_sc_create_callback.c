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
struct vmbus_channel {void (* sc_creation_callback ) (struct vmbus_channel*) ;} ;

/* Variables and functions */

void vmbus_set_sc_create_callback(struct vmbus_channel *primary_channel,
				void (*sc_cr_cb)(struct vmbus_channel *new_sc))
{
	primary_channel->sc_creation_callback = sc_cr_cb;
}