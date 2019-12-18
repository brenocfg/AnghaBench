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
#define  BUFF_FREE 131 
#define  BUFF_LCL 130 
#define  BUFF_USB 129 
#define  BUFF_VALID 128 

__attribute__((used)) static char *buf_state_string(unsigned state)
{
	switch (state) {
	case BUFF_FREE:  return "free";
	case BUFF_VALID: return "valid";
	case BUFF_LCL:   return "local";
	case BUFF_USB:   return "usb";
	default:         return "unknown";
	}
}