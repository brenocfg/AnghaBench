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
struct rtllib_device {int /*<<< orphan*/  active_channel_map; } ;
struct TYPE_2__ {int /*<<< orphan*/  channel_map; } ;

/* Variables and functions */
 TYPE_1__* GET_DOT11D_INFO (struct rtllib_device*) ; 
 scalar_t__ MAX_CHANNEL_NUMBER ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void rtllib_update_active_chan_map(struct rtllib_device *ieee)
{
	memcpy(ieee->active_channel_map, GET_DOT11D_INFO(ieee)->channel_map,
	       MAX_CHANNEL_NUMBER+1);
}