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
 int /*<<< orphan*/  outb (int,int) ; 

__attribute__((used)) static void intel_chipset_set_brightness(int intensity)
{
	outb(0x04 | (intensity << 4), 0xb3);
	outb(0xbf, 0xb2);
}