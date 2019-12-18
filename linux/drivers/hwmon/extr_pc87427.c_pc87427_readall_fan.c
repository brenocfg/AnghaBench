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
typedef  size_t u8 ;
struct pc87427_data {int* address; int /*<<< orphan*/ * fan_status; void** fan_min; void** fan; } ;

/* Variables and functions */
 int /*<<< orphan*/  BANK_FM (size_t) ; 
 size_t LD_FAN ; 
 scalar_t__ PC87427_REG_BANK ; 
 scalar_t__ PC87427_REG_FAN ; 
 scalar_t__ PC87427_REG_FAN_MIN ; 
 scalar_t__ PC87427_REG_FAN_STATUS ; 
 int /*<<< orphan*/  inb (scalar_t__) ; 
 void* inw (scalar_t__) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void pc87427_readall_fan(struct pc87427_data *data, u8 nr)
{
	int iobase = data->address[LD_FAN];

	outb(BANK_FM(nr), iobase + PC87427_REG_BANK);
	data->fan[nr] = inw(iobase + PC87427_REG_FAN);
	data->fan_min[nr] = inw(iobase + PC87427_REG_FAN_MIN);
	data->fan_status[nr] = inb(iobase + PC87427_REG_FAN_STATUS);
	/* Clear fan alarm bits */
	outb(data->fan_status[nr], iobase + PC87427_REG_FAN_STATUS);
}