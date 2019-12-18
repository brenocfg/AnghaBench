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
typedef  int u8 ;

/* Variables and functions */
 unsigned int SCALE (int,int,int) ; 

__attribute__((used)) static inline unsigned int FAN_FROM_REG(u8 reg, u8 div)
{
	if (!reg) /* error */
		return -1;

	if (reg == 255)
		return 0;

	return SCALE(1350000, 1, reg * div);
}