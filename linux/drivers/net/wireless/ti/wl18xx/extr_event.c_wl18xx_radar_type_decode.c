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
typedef  int u8 ;

/* Variables and functions */
#define  RADAR_TYPE_CHIRP 130 
#define  RADAR_TYPE_NONE 129 
#define  RADAR_TYPE_REGULAR 128 

__attribute__((used)) static const char *wl18xx_radar_type_decode(u8 radar_type)
{
	switch (radar_type) {
	case RADAR_TYPE_REGULAR:
		return "REGULAR";
	case RADAR_TYPE_CHIRP:
		return "CHIRP";
	case RADAR_TYPE_NONE:
	default:
		return "N/A";
	}
}