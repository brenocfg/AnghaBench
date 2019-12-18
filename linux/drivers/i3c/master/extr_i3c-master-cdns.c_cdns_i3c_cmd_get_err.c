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
struct cdns_i3c_cmd {int error; } ;
typedef  enum i3c_error_code { ____Placeholder_i3c_error_code } i3c_error_code ;

/* Variables and functions */
#define  CMDR_M0_ERROR 131 
#define  CMDR_M1_ERROR 130 
#define  CMDR_M2_ERROR 129 
#define  CMDR_NACK_RESP 128 
 int I3C_ERROR_M0 ; 
 int I3C_ERROR_M1 ; 
 int I3C_ERROR_M2 ; 
 int I3C_ERROR_UNKNOWN ; 

__attribute__((used)) static enum i3c_error_code cdns_i3c_cmd_get_err(struct cdns_i3c_cmd *cmd)
{
	switch (cmd->error) {
	case CMDR_M0_ERROR:
		return I3C_ERROR_M0;

	case CMDR_M1_ERROR:
		return I3C_ERROR_M1;

	case CMDR_M2_ERROR:
	case CMDR_NACK_RESP:
		return I3C_ERROR_M2;

	default:
		break;
	}

	return I3C_ERROR_UNKNOWN;
}