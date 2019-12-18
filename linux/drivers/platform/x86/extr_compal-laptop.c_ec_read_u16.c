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
 int ec_read_u8 (scalar_t__) ; 

__attribute__((used)) static u16 ec_read_u16(u8 addr)
{
	int hi, lo;
	lo = ec_read_u8(addr);
	hi = ec_read_u8(addr + 1);
	return (hi << 8) + lo;
}