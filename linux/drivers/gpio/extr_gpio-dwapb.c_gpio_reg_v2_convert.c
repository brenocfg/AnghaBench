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
typedef  unsigned int u32 ;

/* Variables and functions */
#define  GPIO_INTMASK 132 
 unsigned int GPIO_INTMASK_V2 ; 
#define  GPIO_INTSTATUS 131 
 unsigned int GPIO_INTSTATUS_V2 ; 
#define  GPIO_INTTYPE_LEVEL 130 
 unsigned int GPIO_INTTYPE_LEVEL_V2 ; 
#define  GPIO_INT_POLARITY 129 
 unsigned int GPIO_INT_POLARITY_V2 ; 
#define  GPIO_PORTA_EOI 128 
 unsigned int GPIO_PORTA_EOI_V2 ; 

__attribute__((used)) static inline u32 gpio_reg_v2_convert(unsigned int offset)
{
	switch (offset) {
	case GPIO_INTMASK:
		return GPIO_INTMASK_V2;
	case GPIO_INTTYPE_LEVEL:
		return GPIO_INTTYPE_LEVEL_V2;
	case GPIO_INT_POLARITY:
		return GPIO_INT_POLARITY_V2;
	case GPIO_INTSTATUS:
		return GPIO_INTSTATUS_V2;
	case GPIO_PORTA_EOI:
		return GPIO_PORTA_EOI_V2;
	}

	return offset;
}