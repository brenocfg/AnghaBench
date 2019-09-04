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
struct bttv {unsigned int svhs; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_bits (int,unsigned int) ; 

__attribute__((used)) static void phytec_muxsel(struct bttv *btv, unsigned int input)
{
	unsigned int mux = input % 4;

	if (input == btv->svhs)
		mux = 0;

	gpio_bits(0x3, mux);
}