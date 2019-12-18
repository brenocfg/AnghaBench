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
 int /*<<< orphan*/  gpio_bits (int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void td3116_latch_value(struct bttv *btv, u32 value)
{
	gpio_bits((1<<18) | 0xff, value);
	gpio_bits((1<<18) | 0xff, (1<<18) | value);
	udelay(1);
	gpio_bits((1<<18) | 0xff, value);
}