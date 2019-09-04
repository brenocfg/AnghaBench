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
typedef  enum ieee1284_phase { ____Placeholder_ieee1284_phase } ieee1284_phase ;

/* Variables and functions */
 int IEEE1284_ADDR ; 
 int IEEE1284_DEVICEID ; 
#define  IEEE1284_MODE_BYTE 129 
#define  IEEE1284_MODE_NIBBLE 128 
 int IEEE1284_PH_FWD_IDLE ; 
 int IEEE1284_PH_REV_IDLE ; 

__attribute__((used)) static enum ieee1284_phase init_phase(int mode)
{
	switch (mode & ~(IEEE1284_DEVICEID
			 | IEEE1284_ADDR)) {
	case IEEE1284_MODE_NIBBLE:
	case IEEE1284_MODE_BYTE:
		return IEEE1284_PH_REV_IDLE;
	}
	return IEEE1284_PH_FWD_IDLE;
}