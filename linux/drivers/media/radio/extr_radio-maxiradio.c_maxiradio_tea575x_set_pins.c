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
struct snd_tea575x {struct maxiradio* private_data; } ;
struct maxiradio {int /*<<< orphan*/  io; } ;

/* Variables and functions */
 int TEA575X_CLK ; 
 int TEA575X_DATA ; 
 int TEA575X_WREN ; 
 int clk ; 
 int data ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int power ; 
 int wren ; 

__attribute__((used)) static void maxiradio_tea575x_set_pins(struct snd_tea575x *tea, u8 pins)
{
	struct maxiradio *dev = tea->private_data;
	u8 bits = 0;

	bits |= (pins & TEA575X_DATA) ? data : 0;
	bits |= (pins & TEA575X_CLK)  ? clk  : 0;
	bits |= (pins & TEA575X_WREN) ? wren : 0;
	bits |= power;

	outb(bits, dev->io);
}