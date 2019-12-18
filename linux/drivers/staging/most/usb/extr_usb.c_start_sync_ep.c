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
typedef  int u16 ;
struct usb_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ DRCI_COMMAND ; 
 scalar_t__ DRCI_REG_BASE ; 
 int drci_wr_reg (struct usb_device*,scalar_t__,int) ; 

__attribute__((used)) static inline int start_sync_ep(struct usb_device *usb_dev, u16 ep)
{
	return drci_wr_reg(usb_dev, DRCI_REG_BASE + DRCI_COMMAND + ep * 16, 1);
}