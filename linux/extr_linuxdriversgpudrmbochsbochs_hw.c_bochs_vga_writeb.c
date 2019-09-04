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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct bochs_device {scalar_t__ mmio; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void bochs_vga_writeb(struct bochs_device *bochs, u16 ioport, u8 val)
{
	if (WARN_ON(ioport < 0x3c0 || ioport > 0x3df))
		return;

	if (bochs->mmio) {
		int offset = ioport - 0x3c0 + 0x400;
		writeb(val, bochs->mmio + offset);
	} else {
		outb(val, ioport);
	}
}