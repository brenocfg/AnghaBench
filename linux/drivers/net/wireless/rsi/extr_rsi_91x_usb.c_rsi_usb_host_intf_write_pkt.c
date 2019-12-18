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
typedef  scalar_t__ u32 ;
struct rsi_hw {int dummy; } ;

/* Variables and functions */
 int BT_EP ; 
 scalar_t__ RSI_COEX_Q ; 
 scalar_t__ RSI_WIFI_DATA_Q ; 
 scalar_t__ RSI_WIFI_MGMT_Q ; 
 int WLAN_EP ; 
 int rsi_write_multiple (struct rsi_hw*,int,int*,scalar_t__) ; 

__attribute__((used)) static int rsi_usb_host_intf_write_pkt(struct rsi_hw *adapter,
				       u8 *pkt,
				       u32 len)
{
	u32 queueno = ((pkt[1] >> 4) & 0x7);
	u8 endpoint;

	endpoint = ((queueno == RSI_WIFI_MGMT_Q || queueno == RSI_WIFI_DATA_Q ||
		     queueno == RSI_COEX_Q) ? WLAN_EP : BT_EP);

	return rsi_write_multiple(adapter,
				  endpoint,
				  (u8 *)pkt,
				  len);
}