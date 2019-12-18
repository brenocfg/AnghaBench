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

/* Variables and functions */
#define  CPCAP_BIT_AUDIO_LOW_PWR 129 
#define  CPCAP_BIT_AUDIO_NORMAL_MODE 128 
 unsigned int REGULATOR_MODE_INVALID ; 
 unsigned int REGULATOR_MODE_NORMAL ; 
 unsigned int REGULATOR_MODE_STANDBY ; 

__attribute__((used)) static unsigned int cpcap_map_mode(unsigned int mode)
{
	switch (mode) {
	case CPCAP_BIT_AUDIO_NORMAL_MODE:
		return REGULATOR_MODE_NORMAL;
	case CPCAP_BIT_AUDIO_LOW_PWR:
		return REGULATOR_MODE_STANDBY;
	default:
		return REGULATOR_MODE_INVALID;
	}
}