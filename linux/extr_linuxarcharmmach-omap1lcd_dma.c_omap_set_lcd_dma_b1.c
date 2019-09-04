#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  void* u16 ;
struct TYPE_2__ {unsigned long addr; int data_type; void* yres; void* xres; } ;

/* Variables and functions */
 TYPE_1__ lcd_dma ; 

void omap_set_lcd_dma_b1(unsigned long addr, u16 fb_xres, u16 fb_yres,
			 int data_type)
{
	lcd_dma.addr = addr;
	lcd_dma.data_type = data_type;
	lcd_dma.xres = fb_xres;
	lcd_dma.yres = fb_yres;
}