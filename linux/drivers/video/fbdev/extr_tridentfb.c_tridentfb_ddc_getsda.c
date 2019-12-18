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
struct tridentfb_par {int /*<<< orphan*/  io_virt; } ;

/* Variables and functions */
 int DDC_SDA_IN ; 
 int /*<<< orphan*/  I2C ; 
 int vga_mm_rcrt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tridentfb_ddc_getsda(void *data)
{
	struct tridentfb_par *par = data;

	return !!(vga_mm_rcrt(par->io_virt, I2C) & DDC_SDA_IN);
}