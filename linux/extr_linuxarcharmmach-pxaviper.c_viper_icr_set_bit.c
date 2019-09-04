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

/* Variables and functions */
 unsigned int VIPER_ICR ; 
 unsigned int icr ; 

__attribute__((used)) static void viper_icr_set_bit(unsigned int bit)
{
	icr |= bit;
	VIPER_ICR = icr;
}