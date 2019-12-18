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
typedef  int u32 ;
typedef  int u16 ;

/* Variables and functions */
#define  SDIO_LOCAL_DEVICE_ID 133 
 int const SDIO_LOCAL_MSK ; 
 int const WLAN_FIFO_MSK ; 
#define  WLAN_IOREG_DEVICE_ID 132 
 int const WLAN_IOREG_MSK ; 
#define  WLAN_RX0FF_DEVICE_ID 131 
 int const WLAN_RX0FF_MSK ; 
#define  WLAN_TX_HIQ_DEVICE_ID 130 
#define  WLAN_TX_LOQ_DEVICE_ID 129 
#define  WLAN_TX_MIQ_DEVICE_ID 128 
 int get_deviceid (int const) ; 

__attribute__((used)) static u32 _cvrt2ftaddr(const u32 addr, u8 *pdevice_id, u16 *poffset)
{
	u8 device_id;
	u16 offset;
	u32 ftaddr;


	device_id = get_deviceid(addr);
	offset = 0;

	switch (device_id) {
	case SDIO_LOCAL_DEVICE_ID:
		offset = addr & SDIO_LOCAL_MSK;
		break;

	case WLAN_TX_HIQ_DEVICE_ID:
	case WLAN_TX_MIQ_DEVICE_ID:
	case WLAN_TX_LOQ_DEVICE_ID:
		offset = addr & WLAN_FIFO_MSK;
		break;

	case WLAN_RX0FF_DEVICE_ID:
		offset = addr & WLAN_RX0FF_MSK;
		break;

	case WLAN_IOREG_DEVICE_ID:
	default:
		device_id = WLAN_IOREG_DEVICE_ID;
		offset = addr & WLAN_IOREG_MSK;
		break;
	}
	ftaddr = (device_id << 13) | offset;

	if (pdevice_id)
		*pdevice_id = device_id;
	if (poffset)
		*poffset = offset;

	return ftaddr;
}