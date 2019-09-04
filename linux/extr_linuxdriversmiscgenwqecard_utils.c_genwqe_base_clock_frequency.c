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

int genwqe_base_clock_frequency(struct genwqe_dev *cd)
{
	u16 speed;		/*         MHz  MHz  MHz  MHz */
	static const int speed_grade[] = { 250, 200, 166, 175 };

	speed = (u16)((cd->slu_unitcfg >> 28) & 0x0full);
	if (speed >= ARRAY_SIZE(speed_grade))
		return 0;	/* illegal value */

	return speed_grade[speed];
}