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
typedef  scalar_t__ u8 ;

/* Variables and functions */
 scalar_t__ clamp_val (unsigned int,int,int) ; 

__attribute__((used)) static u8 step_time_to_reg(unsigned int msec, u8 mode)
{
	return clamp_val((mode ? (msec + 200) / 400 :
					(msec + 50) / 100), 1, 255);
}