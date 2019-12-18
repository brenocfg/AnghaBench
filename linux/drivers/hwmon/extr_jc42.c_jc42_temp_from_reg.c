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
typedef  int s16 ;

/* Variables and functions */
 int sign_extend32 (int,int) ; 

__attribute__((used)) static int jc42_temp_from_reg(s16 reg)
{
	reg = sign_extend32(reg, 12);

	/* convert from 0.0625 to 0.001 resolution */
	return reg * 125 / 2;
}