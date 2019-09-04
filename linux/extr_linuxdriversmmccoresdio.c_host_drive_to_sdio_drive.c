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
#define  MMC_SET_DRIVER_TYPE_A 131 
#define  MMC_SET_DRIVER_TYPE_B 130 
#define  MMC_SET_DRIVER_TYPE_C 129 
#define  MMC_SET_DRIVER_TYPE_D 128 
 unsigned char SDIO_DTSx_SET_TYPE_A ; 
 unsigned char SDIO_DTSx_SET_TYPE_B ; 
 unsigned char SDIO_DTSx_SET_TYPE_C ; 
 unsigned char SDIO_DTSx_SET_TYPE_D ; 

__attribute__((used)) static unsigned char host_drive_to_sdio_drive(int host_strength)
{
	switch (host_strength) {
	case MMC_SET_DRIVER_TYPE_A:
		return SDIO_DTSx_SET_TYPE_A;
	case MMC_SET_DRIVER_TYPE_B:
		return SDIO_DTSx_SET_TYPE_B;
	case MMC_SET_DRIVER_TYPE_C:
		return SDIO_DTSx_SET_TYPE_C;
	case MMC_SET_DRIVER_TYPE_D:
		return SDIO_DTSx_SET_TYPE_D;
	default:
		return SDIO_DTSx_SET_TYPE_B;
	}
}