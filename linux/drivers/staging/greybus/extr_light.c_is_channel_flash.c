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
struct gb_channel {int mode; } ;

/* Variables and functions */
 int GB_CHANNEL_MODE_FLASH ; 
 int GB_CHANNEL_MODE_INDICATOR ; 
 int GB_CHANNEL_MODE_TORCH ; 

__attribute__((used)) static bool is_channel_flash(struct gb_channel *channel)
{
	return !!(channel->mode & (GB_CHANNEL_MODE_FLASH | GB_CHANNEL_MODE_TORCH
				   | GB_CHANNEL_MODE_INDICATOR));
}