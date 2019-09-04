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
typedef  scalar_t__ u32 ;
struct usb_dmac_chan {scalar_t__ iomem; } ;

/* Variables and functions */
 scalar_t__ readl (scalar_t__) ; 

__attribute__((used)) static u32 usb_dmac_chan_read(struct usb_dmac_chan *chan, u32 reg)
{
	return readl(chan->iomem + reg);
}