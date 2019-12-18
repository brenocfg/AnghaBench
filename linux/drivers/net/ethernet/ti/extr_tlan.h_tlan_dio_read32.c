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
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;

/* Variables and functions */
 scalar_t__ TLAN_DIO_ADR ; 
 scalar_t__ TLAN_DIO_DATA ; 
 int /*<<< orphan*/  inl (scalar_t__) ; 
 int /*<<< orphan*/  outw (scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline u32 tlan_dio_read32(u16 base_addr, u16 internal_addr)
{
	outw(internal_addr, base_addr + TLAN_DIO_ADR);
	return inl(base_addr + TLAN_DIO_DATA);

}