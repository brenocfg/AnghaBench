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
struct pc87427_data {int* address; int /*<<< orphan*/ * pwm_enable; } ;

/* Variables and functions */
 size_t LD_FAN ; 
 scalar_t__ PC87427_REG_PWM_ENABLE ; 
 int /*<<< orphan*/  PWM_ENABLE_MODE_MASK ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void update_pwm_enable(struct pc87427_data *data, int nr, u8 mode)
{
	int iobase = data->address[LD_FAN];
	data->pwm_enable[nr] &= ~PWM_ENABLE_MODE_MASK;
	data->pwm_enable[nr] |= mode;
	outb(data->pwm_enable[nr], iobase + PC87427_REG_PWM_ENABLE);
}