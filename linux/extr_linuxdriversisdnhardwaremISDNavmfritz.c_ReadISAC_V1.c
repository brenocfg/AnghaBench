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
typedef  int u8 ;
struct fritzcard {scalar_t__ addr; } ;

/* Variables and functions */
 int AVM_ISAC_REG_HIGH ; 
 int AVM_ISAC_REG_LOW ; 
 scalar_t__ CHIP_INDEX ; 
 scalar_t__ CHIP_WINDOW ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static u8
ReadISAC_V1(void *p, u8 offset)
{
	struct fritzcard *fc = p;
	u8 idx = (offset > 0x2f) ? AVM_ISAC_REG_HIGH : AVM_ISAC_REG_LOW;

	outb(idx, fc->addr + CHIP_INDEX);
	return inb(fc->addr + CHIP_WINDOW + (offset & 0xf));
}