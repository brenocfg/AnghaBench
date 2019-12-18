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
struct bttv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT848_GPIO_REG_INP ; 
 int /*<<< orphan*/  btwrite (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_inout (int,int) ; 
 int /*<<< orphan*/  gpio_write (int) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static void init_lmlbt4x(struct bttv *btv)
{
	pr_debug("LMLBT4x init\n");
	btwrite(0x000000, BT848_GPIO_REG_INP);
	gpio_inout(0xffffff, 0x0006C0);
	gpio_write(0x000000);
}