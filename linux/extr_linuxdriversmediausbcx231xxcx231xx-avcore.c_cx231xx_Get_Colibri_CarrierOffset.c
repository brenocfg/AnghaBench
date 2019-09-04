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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ TUNER_MODE_FM_RADIO ; 
 scalar_t__ V4L2_STD_MN ; 
 scalar_t__ V4L2_STD_NTSC_M_JP ; 
 scalar_t__ V4L2_STD_PAL_B ; 
 scalar_t__ V4L2_STD_PAL_D ; 
 scalar_t__ V4L2_STD_PAL_G ; 
 scalar_t__ V4L2_STD_PAL_I ; 
 scalar_t__ V4L2_STD_SECAM ; 

u32 cx231xx_Get_Colibri_CarrierOffset(u32 mode, u32 standerd)
{
	u32 colibri_carrier_offset = 0;

	if (mode == TUNER_MODE_FM_RADIO) {
		colibri_carrier_offset = 1100000;
	} else if (standerd & (V4L2_STD_MN | V4L2_STD_NTSC_M_JP)) {
		colibri_carrier_offset = 4832000;  /*4.83MHz	*/
	} else if (standerd & (V4L2_STD_PAL_B | V4L2_STD_PAL_G)) {
		colibri_carrier_offset = 2700000;  /*2.70MHz       */
	} else if (standerd & (V4L2_STD_PAL_D | V4L2_STD_PAL_I
			| V4L2_STD_SECAM)) {
		colibri_carrier_offset = 2100000;  /*2.10MHz	*/
	}

	return colibri_carrier_offset;
}