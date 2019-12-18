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
typedef  int u32 ;

/* Variables and functions */

__attribute__((used)) static inline void stm32_fmc2_ham_set_ecc(const u32 ecc_sta, u8 *ecc)
{
	ecc[0] = ecc_sta;
	ecc[1] = ecc_sta >> 8;
	ecc[2] = ecc_sta >> 16;
}