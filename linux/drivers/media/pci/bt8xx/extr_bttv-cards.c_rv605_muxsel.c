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
struct bttv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_bits (int,int const) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static void rv605_muxsel(struct bttv *btv, unsigned int input)
{
	static const u8 muxgpio[] = { 0x3, 0x1, 0x2, 0x4, 0xf, 0x7, 0xe, 0x0,
				      0xd, 0xb, 0xc, 0x6, 0x9, 0x5, 0x8, 0xa };

	gpio_bits(0x07f, muxgpio[input]);

	/* reset all connections */
	gpio_bits(0x200,0x200);
	mdelay(1);
	gpio_bits(0x200,0x000);
	mdelay(1);

	/* create a new connection */
	gpio_bits(0x480,0x480);
	mdelay(1);
	gpio_bits(0x480,0x080);
	mdelay(1);
}