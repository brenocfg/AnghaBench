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
typedef  unsigned int u8 ;

/* Variables and functions */
 unsigned int ADC_SRC_4020_MASK ; 

__attribute__((used)) static inline u8 adc_src_4020_bits(unsigned int source)
{
	return (source << 4) & ADC_SRC_4020_MASK;
}