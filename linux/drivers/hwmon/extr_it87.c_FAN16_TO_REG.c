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
typedef  int u16 ;

/* Variables and functions */
 int clamp_val (int,int,int) ; 

__attribute__((used)) static inline u16 FAN16_TO_REG(long rpm)
{
	if (rpm == 0)
		return 0xffff;
	return clamp_val((1350000 + rpm) / (rpm * 2), 1, 0xfffe);
}