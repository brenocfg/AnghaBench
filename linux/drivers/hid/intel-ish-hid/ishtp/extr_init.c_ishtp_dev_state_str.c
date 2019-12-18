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
#define  ISHTP_DEV_DISABLED 134 
#define  ISHTP_DEV_ENABLED 133 
#define  ISHTP_DEV_INITIALIZING 132 
#define  ISHTP_DEV_INIT_CLIENTS 131 
#define  ISHTP_DEV_POWER_DOWN 130 
#define  ISHTP_DEV_POWER_UP 129 
#define  ISHTP_DEV_RESETTING 128 

const char *ishtp_dev_state_str(int state)
{
	switch (state) {
	case ISHTP_DEV_INITIALIZING:
		return	"INITIALIZING";
	case ISHTP_DEV_INIT_CLIENTS:
		return	"INIT_CLIENTS";
	case ISHTP_DEV_ENABLED:
		return	"ENABLED";
	case ISHTP_DEV_RESETTING:
		return	"RESETTING";
	case ISHTP_DEV_DISABLED:
		return	"DISABLED";
	case ISHTP_DEV_POWER_DOWN:
		return	"POWER_DOWN";
	case ISHTP_DEV_POWER_UP:
		return	"POWER_UP";
	default:
		return "unknown";
	}
}