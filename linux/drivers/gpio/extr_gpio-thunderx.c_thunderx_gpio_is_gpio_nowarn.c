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
typedef  int u64 ;
struct thunderx_gpio {scalar_t__ register_base; } ;

/* Variables and functions */
 int GPIO_BIT_CFG_PIN_SEL_MASK ; 
 scalar_t__ bit_cfg_reg (unsigned int) ; 
 int readq (scalar_t__) ; 

__attribute__((used)) static bool thunderx_gpio_is_gpio_nowarn(struct thunderx_gpio *txgpio,
					 unsigned int line)
{
	u64 bit_cfg = readq(txgpio->register_base + bit_cfg_reg(line));

	return (bit_cfg & GPIO_BIT_CFG_PIN_SEL_MASK) == 0;
}