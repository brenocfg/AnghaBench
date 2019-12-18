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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ ASIC_QSFP1_IN ; 
 scalar_t__ ASIC_QSFP2_IN ; 

__attribute__((used)) static inline u32 i2c_in_csr(u32 bus_num)
{
	return bus_num ? ASIC_QSFP2_IN : ASIC_QSFP1_IN;
}