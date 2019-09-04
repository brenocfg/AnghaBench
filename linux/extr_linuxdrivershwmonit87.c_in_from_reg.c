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
struct it87_data {int dummy; } ;

/* Variables and functions */
 int DIV_ROUND_CLOSEST (int,int) ; 
 int adc_lsb (struct it87_data const*,int) ; 

__attribute__((used)) static int in_from_reg(const struct it87_data *data, int nr, int val)
{
	return DIV_ROUND_CLOSEST(val * adc_lsb(data, nr), 10);
}