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
typedef  int u16 ;

/* Variables and functions */
#define  CONNECT_ERR_ASSOC_ERR_AUTH_REFUSED 132 
#define  CONNECT_ERR_ASSOC_ERR_TIMEOUT 131 
#define  CONNECT_ERR_AUTH_ERR_STA_FAILURE 130 
#define  CONNECT_ERR_AUTH_MSG_UNHANDLED 129 
#define  CONNECT_ERR_STA_FAILURE 128 

__attribute__((used)) static const char *assoc_failure_reason_to_str(u16 cap_info)
{
	switch (cap_info) {
	case CONNECT_ERR_AUTH_ERR_STA_FAILURE:
		return "CONNECT_ERR_AUTH_ERR_STA_FAILURE";
	case CONNECT_ERR_AUTH_MSG_UNHANDLED:
		return "CONNECT_ERR_AUTH_MSG_UNHANDLED";
	case CONNECT_ERR_ASSOC_ERR_TIMEOUT:
		return "CONNECT_ERR_ASSOC_ERR_TIMEOUT";
	case CONNECT_ERR_ASSOC_ERR_AUTH_REFUSED:
		return "CONNECT_ERR_ASSOC_ERR_AUTH_REFUSED";
	case CONNECT_ERR_STA_FAILURE:
		return "CONNECT_ERR_STA_FAILURE";
	}

	return "Unknown connect failure";
}