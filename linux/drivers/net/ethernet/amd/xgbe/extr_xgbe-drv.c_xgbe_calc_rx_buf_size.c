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
struct net_device {int dummy; } ;

/* Variables and functions */
 unsigned int ETH_FCS_LEN ; 
 unsigned int ETH_HLEN ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 unsigned int VLAN_HLEN ; 
 unsigned int XGBE_RX_BUF_ALIGN ; 
 int /*<<< orphan*/  XGBE_RX_MIN_BUF_SIZE ; 
 unsigned int clamp_val (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xgbe_calc_rx_buf_size(struct net_device *netdev, unsigned int mtu)
{
	unsigned int rx_buf_size;

	rx_buf_size = mtu + ETH_HLEN + ETH_FCS_LEN + VLAN_HLEN;
	rx_buf_size = clamp_val(rx_buf_size, XGBE_RX_MIN_BUF_SIZE, PAGE_SIZE);

	rx_buf_size = (rx_buf_size + XGBE_RX_BUF_ALIGN - 1) &
		      ~(XGBE_RX_BUF_ALIGN - 1);

	return rx_buf_size;
}