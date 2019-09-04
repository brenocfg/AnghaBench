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
struct pc87427_data {int* address; void** pwm; void** pwm_enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  BANK_FC (size_t) ; 
 size_t LD_FAN ; 
 scalar_t__ PC87427_REG_BANK ; 
 scalar_t__ PC87427_REG_PWM_DUTY ; 
 scalar_t__ PC87427_REG_PWM_ENABLE ; 
 void* inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void pc87427_readall_pwm(struct pc87427_data *data, u8 nr)
{
	int iobase = data->address[LD_FAN];

	outb(BANK_FC(nr), iobase + PC87427_REG_BANK);
	data->pwm_enable[nr] = inb(iobase + PC87427_REG_PWM_ENABLE);
	data->pwm[nr] = inb(iobase + PC87427_REG_PWM_DUTY);
}