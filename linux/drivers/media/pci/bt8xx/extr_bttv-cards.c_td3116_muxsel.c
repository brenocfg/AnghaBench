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
typedef  int u32 ;
struct bttv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  td3116_latch_value (struct bttv*,int) ; 

__attribute__((used)) static void td3116_muxsel(struct bttv *btv, unsigned int input)
{
	u32 value;
	u32 highbit;

	highbit = (input & 0x8) >> 3 ;

	/* Disable outputs and set value in the mux */
	value = 0x11; /* Disable outputs */
	value |= ((input & 0x7) << 1)  << (4 * highbit);
	td3116_latch_value(btv, value);

	/* Enable the correct output */
	value &= ~0x11;
	value |= ((highbit ^ 0x1) << 4) | highbit;
	td3116_latch_value(btv, value);
}