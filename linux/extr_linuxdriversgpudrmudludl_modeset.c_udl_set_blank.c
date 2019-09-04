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
#define  DRM_MODE_DPMS_OFF 131 
#define  DRM_MODE_DPMS_ON 130 
#define  DRM_MODE_DPMS_STANDBY 129 
#define  DRM_MODE_DPMS_SUSPEND 128 
 char* udl_set_register (char*,int,int) ; 

__attribute__((used)) static char *udl_set_blank(char *buf, int dpms_mode)
{
	u8 reg;
	switch (dpms_mode) {
	case DRM_MODE_DPMS_OFF:
		reg = 0x07;
		break;
	case DRM_MODE_DPMS_STANDBY:
		reg = 0x05;
		break;
	case DRM_MODE_DPMS_SUSPEND:
		reg = 0x01;
		break;
	case DRM_MODE_DPMS_ON:
		reg = 0x00;
		break;
	}

	return udl_set_register(buf, 0x1f, reg);
}