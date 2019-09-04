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

/* Variables and functions */
 int AD5791_LINCOMP_0_10 ; 
 int AD5791_LINCOMP_10_12 ; 
 int AD5791_LINCOMP_12_16 ; 
 int AD5791_LINCOMP_16_19 ; 
 int AD5791_LINCOMP_19_20 ; 

__attribute__((used)) static int ad5791_get_lin_comp(unsigned int span)
{
	if (span <= 10000)
		return AD5791_LINCOMP_0_10;
	else if (span <= 12000)
		return AD5791_LINCOMP_10_12;
	else if (span <= 16000)
		return AD5791_LINCOMP_12_16;
	else if (span <= 19000)
		return AD5791_LINCOMP_16_19;
	else
		return AD5791_LINCOMP_19_20;
}