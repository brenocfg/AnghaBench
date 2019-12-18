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
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 scalar_t__ MEDIA_BUS_FMT_BGR888_1X24 ; 
 scalar_t__ MEDIA_BUS_FMT_BGR888_3X8 ; 
 scalar_t__ MEDIA_BUS_FMT_UYVY8_1X16 ; 
 scalar_t__ MEDIA_BUS_FMT_UYVY8_2X8 ; 

__attribute__((used)) static __u32 serial_to_parallel_code(__u32 serial)
{
	if (serial == MEDIA_BUS_FMT_UYVY8_1X16)
		return MEDIA_BUS_FMT_UYVY8_2X8;
	if (serial == MEDIA_BUS_FMT_BGR888_1X24)
		return MEDIA_BUS_FMT_BGR888_3X8;

	return serial;
}