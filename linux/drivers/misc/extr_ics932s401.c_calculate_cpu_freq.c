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
struct ics932s401_data {int* regs; } ;

/* Variables and functions */
 int BASE_CLOCK ; 
 size_t ICS932S401_CPU_DIVISOR_SHIFT ; 
 int ICS932S401_M_MASK ; 
 size_t ICS932S401_REG_CPU_DIVISOR ; 
 size_t ICS932S401_REG_CPU_M_CTRL ; 
 size_t ICS932S401_REG_CPU_N_CTRL ; 
 int* divisors ; 

__attribute__((used)) static int calculate_cpu_freq(struct ics932s401_data *data)
{
	int m, n, freq;

	m = data->regs[ICS932S401_REG_CPU_M_CTRL] & ICS932S401_M_MASK;
	n = data->regs[ICS932S401_REG_CPU_N_CTRL];

	/* Pull in bits 8 & 9 from the M register */
	n |= ((int)data->regs[ICS932S401_REG_CPU_M_CTRL] & 0x80) << 1;
	n |= ((int)data->regs[ICS932S401_REG_CPU_M_CTRL] & 0x40) << 3;

	freq = BASE_CLOCK * (n + 8) / (m + 2);
	freq /= divisors[data->regs[ICS932S401_REG_CPU_DIVISOR] >>
			 ICS932S401_CPU_DIVISOR_SHIFT];

	return freq;
}