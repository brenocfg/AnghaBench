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
typedef  enum chip_type { ____Placeholder_chip_type } chip_type ;

/* Variables and functions */
 int CFG2_32BIT ; 
 scalar_t__ REG_CFG2 ; 
 scalar_t__ REG_ID_LSB ; 
 scalar_t__ REG_ID_MSB ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int tmc1800 ; 
 int tmc18c30 ; 
 int tmc18c50 ; 
 int unknown ; 

__attribute__((used)) static enum chip_type fdomain_identify(int port)
{
	u16 id = inb(port + REG_ID_LSB) | inb(port + REG_ID_MSB) << 8;

	switch (id) {
	case 0x6127:
		return tmc1800;
	case 0x60e9: /* 18c50 or 18c30 */
		break;
	default:
		return unknown;
	}

	/* Try to toggle 32-bit mode. This only works on an 18c30 chip. */
	outb(CFG2_32BIT, port + REG_CFG2);
	if ((inb(port + REG_CFG2) & CFG2_32BIT)) {
		outb(0, port + REG_CFG2);
		if ((inb(port + REG_CFG2) & CFG2_32BIT) == 0)
			return tmc18c30;
	}
	/* If that failed, we are an 18c50. */
	return tmc18c50;
}