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
struct ci_hw_ep {scalar_t__ dir; int num; } ;

/* Variables and functions */
 scalar_t__ TX ; 
 int USB_ENDPOINT_DIR_MASK ; 

__attribute__((used)) static inline u8 _usb_addr(struct ci_hw_ep *ep)
{
	return ((ep->dir == TX) ? USB_ENDPOINT_DIR_MASK : 0) | ep->num;
}