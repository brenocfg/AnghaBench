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
typedef  int u16 ;
struct bochs_device {scalar_t__ mmio; } ;

/* Variables and functions */
 int /*<<< orphan*/  VBE_DISPI_IOPORT_DATA ; 
 int /*<<< orphan*/  VBE_DISPI_IOPORT_INDEX ; 
 int /*<<< orphan*/  outw (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static void bochs_dispi_write(struct bochs_device *bochs, u16 reg, u16 val)
{
	if (bochs->mmio) {
		int offset = 0x500 + (reg << 1);
		writew(val, bochs->mmio + offset);
	} else {
		outw(reg, VBE_DISPI_IOPORT_INDEX);
		outw(val, VBE_DISPI_IOPORT_DATA);
	}
}