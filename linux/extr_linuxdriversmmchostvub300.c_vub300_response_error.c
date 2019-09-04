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
 int EILSEQ ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEDIUM ; 
 int ETIMEDOUT ; 
#define  SD_ERROR_1BIT_CRC_ERROR 149 
#define  SD_ERROR_1BIT_CRC_WRONG 148 
#define  SD_ERROR_1BIT_DATA_TIMEOUT 147 
#define  SD_ERROR_1BIT_TIMEOUT 146 
#define  SD_ERROR_1BIT_UNEXPECTED_TIMEOUT 145 
#define  SD_ERROR_4BIT_CRC_ERROR 144 
#define  SD_ERROR_4BIT_CRC_WRONG 143 
#define  SD_ERROR_4BIT_DATA_TIMEOUT 142 
#define  SD_ERROR_4BIT_TIMEOUT 141 
#define  SD_ERROR_4BIT_UNEXPECTED_TIMEOUT 140 
#define  SD_ERROR_ILLEGAL_COMMAND 139 
#define  SD_ERROR_NO_1BIT_DATEND 138 
#define  SD_ERROR_NO_4BIT_DATEND 137 
#define  SD_ERROR_NO_CMD_ENDBIT 136 
#define  SD_ERROR_NO_DEVICE 135 
#define  SD_ERROR_OVERRUN 134 
#define  SD_ERROR_PIO_TIMEOUT 133 
#define  SD_ERROR_SDCRDY_STUCK 132 
#define  SD_ERROR_STAT_CMD 131 
#define  SD_ERROR_STAT_CMD_TIMEOUT 130 
#define  SD_ERROR_STAT_DATA 129 
#define  SD_ERROR_UNHANDLED 128 

__attribute__((used)) static int vub300_response_error(u8 error_code)
{
	switch (error_code) {
	case SD_ERROR_PIO_TIMEOUT:
	case SD_ERROR_1BIT_TIMEOUT:
	case SD_ERROR_4BIT_TIMEOUT:
		return -ETIMEDOUT;
	case SD_ERROR_STAT_DATA:
	case SD_ERROR_OVERRUN:
	case SD_ERROR_STAT_CMD:
	case SD_ERROR_STAT_CMD_TIMEOUT:
	case SD_ERROR_SDCRDY_STUCK:
	case SD_ERROR_UNHANDLED:
	case SD_ERROR_1BIT_CRC_WRONG:
	case SD_ERROR_4BIT_CRC_WRONG:
	case SD_ERROR_1BIT_CRC_ERROR:
	case SD_ERROR_4BIT_CRC_ERROR:
	case SD_ERROR_NO_CMD_ENDBIT:
	case SD_ERROR_NO_1BIT_DATEND:
	case SD_ERROR_NO_4BIT_DATEND:
	case SD_ERROR_1BIT_DATA_TIMEOUT:
	case SD_ERROR_4BIT_DATA_TIMEOUT:
	case SD_ERROR_1BIT_UNEXPECTED_TIMEOUT:
	case SD_ERROR_4BIT_UNEXPECTED_TIMEOUT:
		return -EILSEQ;
	case 33:
		return -EILSEQ;
	case SD_ERROR_ILLEGAL_COMMAND:
		return -EINVAL;
	case SD_ERROR_NO_DEVICE:
		return -ENOMEDIUM;
	default:
		return -ENODEV;
	}
}