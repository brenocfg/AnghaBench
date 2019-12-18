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
 int /*<<< orphan*/  gpio_inout (int,int) ; 
 int /*<<< orphan*/  gpio_write (int) ; 

__attribute__((used)) static void tibetCS16_init(struct bttv *btv)
{
	/* enable gpio bits, mask obtained via btSpy */
	gpio_inout(0xffffff, 0x0f7fff);
	gpio_write(0x0f7fff);
}