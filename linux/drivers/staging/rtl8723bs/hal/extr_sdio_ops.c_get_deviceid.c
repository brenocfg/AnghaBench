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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int u16 ;

/* Variables and functions */
 int /*<<< orphan*/  SDIO_LOCAL_DEVICE_ID ; 
 int /*<<< orphan*/  WLAN_IOREG_DEVICE_ID ; 
 int /*<<< orphan*/  WLAN_RX0FF_DEVICE_ID ; 
 int /*<<< orphan*/  WLAN_TX_HIQ_DEVICE_ID ; 
 int /*<<< orphan*/  WLAN_TX_LOQ_DEVICE_ID ; 
 int /*<<< orphan*/  WLAN_TX_MIQ_DEVICE_ID ; 

__attribute__((used)) static u8 get_deviceid(u32 addr)
{
	u8 devide_id;
	u16 pseudo_id;


	pseudo_id = (u16)(addr >> 16);
	switch (pseudo_id) {
	case 0x1025:
		devide_id = SDIO_LOCAL_DEVICE_ID;
		break;

	case 0x1026:
		devide_id = WLAN_IOREG_DEVICE_ID;
		break;

/* 		case 0x1027: */
/* 			devide_id = SDIO_FIRMWARE_FIFO; */
/* 			break; */

	case 0x1031:
		devide_id = WLAN_TX_HIQ_DEVICE_ID;
		break;

	case 0x1032:
		devide_id = WLAN_TX_MIQ_DEVICE_ID;
		break;

	case 0x1033:
		devide_id = WLAN_TX_LOQ_DEVICE_ID;
		break;

	case 0x1034:
		devide_id = WLAN_RX0FF_DEVICE_ID;
		break;

	default:
/* 			devide_id = (u8)((addr >> 13) & 0xF); */
		devide_id = WLAN_IOREG_DEVICE_ID;
		break;
	}

	return devide_id;
}