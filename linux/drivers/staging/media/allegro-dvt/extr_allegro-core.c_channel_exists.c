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
struct allegro_channel {int mcu_channel_id; } ;

/* Variables and functions */

__attribute__((used)) static inline bool channel_exists(struct allegro_channel *channel)
{
	return channel->mcu_channel_id != -1;
}