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
typedef  int u16 ;
struct f71805f_data {scalar_t__ addr; } ;

/* Variables and functions */
 scalar_t__ ADDR_REG_OFFSET ; 
 scalar_t__ DATA_REG_OFFSET ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static void f71805f_write16(struct f71805f_data *data, u8 reg, u16 val)
{
	outb(reg, data->addr + ADDR_REG_OFFSET);
	outb(val >> 8, data->addr + DATA_REG_OFFSET);
	outb(++reg, data->addr + ADDR_REG_OFFSET);
	outb(val & 0xff, data->addr + DATA_REG_OFFSET);
}