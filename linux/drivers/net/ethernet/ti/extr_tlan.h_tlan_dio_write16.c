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
 int TLAN_DIO_ADR ; 
 int TLAN_DIO_DATA ; 
 int /*<<< orphan*/  outw (int,int) ; 

__attribute__((used)) static inline void tlan_dio_write16(u16 base_addr, u16 internal_addr, u16 data)
{
	outw(internal_addr, base_addr + TLAN_DIO_ADR);
	outw(data, base_addr + TLAN_DIO_DATA + (internal_addr & 0x2));

}