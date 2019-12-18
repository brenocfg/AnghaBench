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
 int EAGAIN ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
#define  WMI_RF_SECTOR_STATUS_BAD_PARAMETERS_ERROR 131 
#define  WMI_RF_SECTOR_STATUS_BUSY_ERROR 130 
#define  WMI_RF_SECTOR_STATUS_NOT_SUPPORTED_ERROR 129 
#define  WMI_RF_SECTOR_STATUS_SUCCESS 128 

__attribute__((used)) static int wil_rf_sector_status_to_rc(u8 status)
{
	switch (status) {
	case WMI_RF_SECTOR_STATUS_SUCCESS:
		return 0;
	case WMI_RF_SECTOR_STATUS_BAD_PARAMETERS_ERROR:
		return -EINVAL;
	case WMI_RF_SECTOR_STATUS_BUSY_ERROR:
		return -EAGAIN;
	case WMI_RF_SECTOR_STATUS_NOT_SUPPORTED_ERROR:
		return -EOPNOTSUPP;
	default:
		return -EINVAL;
	}
}