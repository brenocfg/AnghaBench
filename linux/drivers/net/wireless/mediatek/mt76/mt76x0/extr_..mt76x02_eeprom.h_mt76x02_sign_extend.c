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
typedef  int u32 ;

/* Variables and functions */
 int BIT (unsigned int) ; 

__attribute__((used)) static inline int
mt76x02_sign_extend(u32 val, unsigned int size)
{
	bool sign = val & BIT(size - 1);

	val &= BIT(size - 1) - 1;

	return sign ? val : -val;
}