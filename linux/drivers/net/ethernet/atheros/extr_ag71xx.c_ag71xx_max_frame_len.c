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
 unsigned int ETH_FCS_LEN ; 
 unsigned int ETH_HLEN ; 
 unsigned int ETH_SWITCH_HEADER_LEN ; 
 unsigned int VLAN_HLEN ; 

__attribute__((used)) static unsigned int ag71xx_max_frame_len(unsigned int mtu)
{
	return ETH_SWITCH_HEADER_LEN + ETH_HLEN + VLAN_HLEN + mtu + ETH_FCS_LEN;
}