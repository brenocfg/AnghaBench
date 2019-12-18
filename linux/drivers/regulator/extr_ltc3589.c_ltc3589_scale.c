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
typedef  int uint64_t ;
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  do_div (int,int) ; 

__attribute__((used)) static inline unsigned int ltc3589_scale(unsigned int uV, u32 r1, u32 r2)
{
	uint64_t tmp;

	if (uV == 0)
		return 0;

	tmp = (uint64_t)uV * r1;
	do_div(tmp, r2);
	return uV + (unsigned int)tmp;
}