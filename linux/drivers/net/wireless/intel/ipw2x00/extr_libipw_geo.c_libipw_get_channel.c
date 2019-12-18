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
typedef  scalar_t__ u8 ;
struct TYPE_2__ {struct libipw_channel const* a; struct libipw_channel const* bg; } ;
struct libipw_device {TYPE_1__ geo; } ;
struct libipw_channel {int dummy; } ;

/* Variables and functions */
 scalar_t__ LIBIPW_24GHZ_CHANNELS ; 
 struct libipw_channel const bad_channel ; 
 int libipw_channel_to_index (struct libipw_device*,scalar_t__) ; 

const struct libipw_channel *libipw_get_channel(struct libipw_device
						      *ieee, u8 channel)
{
	int index = libipw_channel_to_index(ieee, channel);

	if (index == -1)
		return &bad_channel;

	if (channel <= LIBIPW_24GHZ_CHANNELS)
		return &ieee->geo.bg[index];

	return &ieee->geo.a[index];
}