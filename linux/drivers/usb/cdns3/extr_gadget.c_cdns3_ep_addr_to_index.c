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
 int USB_DIR_IN ; 

u8 cdns3_ep_addr_to_index(u8 ep_addr)
{
	return (((ep_addr & 0x7F)) + ((ep_addr & USB_DIR_IN) ? 16 : 0));
}