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
typedef  int u16 ;

/* Variables and functions */
 char* udl_set_register (char*,scalar_t__,int) ; 

__attribute__((used)) static char *udl_set_register_16(char *wrptr, u8 reg, u16 value)
{
	wrptr = udl_set_register(wrptr, reg, value >> 8);
	return udl_set_register(wrptr, reg+1, value);
}