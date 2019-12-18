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

/* Variables and functions */
 scalar_t__ STATE_FRESH ; 
 scalar_t__ inb (int) ; 
 int /*<<< orphan*/  outb (int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void __device_refresh(void)
{
	udelay(200);
	if (inb(0x1604) != STATE_FRESH) {
		outb(0x11, 0x1610);
		outb(0x01, 0x161f);
	}
}