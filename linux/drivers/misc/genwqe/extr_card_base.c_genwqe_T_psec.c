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
typedef  size_t u16 ;
struct genwqe_dev {int slu_unitcfg; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (int const*) ; 

__attribute__((used)) static int genwqe_T_psec(struct genwqe_dev *cd)
{
	u16 speed;	/* 1/f -> 250,  200,  166,  175 */
	static const int T[] = { 4000, 5000, 6000, 5714 };

	speed = (u16)((cd->slu_unitcfg >> 28) & 0x0full);
	if (speed >= ARRAY_SIZE(T))
		return -1;	/* illegal value */

	return T[speed];
}