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
struct rtsx_chip {scalar_t__ asic_code; } ;

/* Variables and functions */
 int switch_normal_clock (struct rtsx_chip*,int) ; 
 int switch_ssc_clock (struct rtsx_chip*,int) ; 

__attribute__((used)) static inline int switch_clock(struct rtsx_chip *chip, int clk)
{
	int retval = 0;

	if (chip->asic_code)
		retval = switch_ssc_clock(chip, clk);
	else
		retval = switch_normal_clock(chip, clk);

	return retval;
}