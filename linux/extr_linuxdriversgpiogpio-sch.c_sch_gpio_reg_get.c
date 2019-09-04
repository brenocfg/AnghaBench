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
struct sch_gpio {scalar_t__ iobase; } ;

/* Variables and functions */
 int BIT (unsigned short) ; 
 int inb (scalar_t__) ; 
 unsigned short sch_gpio_bit (struct sch_gpio*,unsigned int) ; 
 unsigned short sch_gpio_offset (struct sch_gpio*,unsigned int,unsigned int) ; 

__attribute__((used)) static int sch_gpio_reg_get(struct sch_gpio *sch, unsigned gpio, unsigned reg)
{
	unsigned short offset, bit;
	u8 reg_val;

	offset = sch_gpio_offset(sch, gpio, reg);
	bit = sch_gpio_bit(sch, gpio);

	reg_val = !!(inb(sch->iobase + offset) & BIT(bit));

	return reg_val;
}