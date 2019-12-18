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
typedef  int u32 ;

/* Variables and functions */
 scalar_t__ ADT ; 
 int ADT0_CE_BIT ; 
 int ADT0_LE_BIT ; 
 int ADT0_PG_BIT ; 
 int /*<<< orphan*/  dim2_write_ctr (scalar_t__,int*) ; 

__attribute__((used)) static void dim2_configure_adt(u8 ch_addr)
{
	u32 adt[4] = { 0, 0, 0, 0 };

	adt[0] =
		(true << ADT0_CE_BIT) |
		(true << ADT0_LE_BIT) |
		(0 << ADT0_PG_BIT);

	dim2_write_ctr(ADT + ch_addr, adt);
}