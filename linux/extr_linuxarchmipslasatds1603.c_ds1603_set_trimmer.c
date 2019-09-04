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
 unsigned int TRIMMER_SET_CMD ; 
 unsigned int TRIMMER_SHIFT ; 
 unsigned int TRIMMER_VALUE_MASK ; 
 int /*<<< orphan*/  rtc_end_op () ; 
 int /*<<< orphan*/  rtc_init_op () ; 
 int /*<<< orphan*/  rtc_write_byte (unsigned int) ; 

void ds1603_set_trimmer(unsigned int trimval)
{
	rtc_init_op();
	rtc_write_byte(((trimval << TRIMMER_SHIFT) & TRIMMER_VALUE_MASK)
			| (TRIMMER_SET_CMD));
	rtc_end_op();
}