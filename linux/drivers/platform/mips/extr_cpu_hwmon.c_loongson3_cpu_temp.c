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
 int LOONGSON_CHIPTEMP (int) ; 
#define  PRID_REV_LOONGSON3A_R1 134 
#define  PRID_REV_LOONGSON3A_R2_0 133 
#define  PRID_REV_LOONGSON3A_R2_1 132 
#define  PRID_REV_LOONGSON3A_R3_0 131 
#define  PRID_REV_LOONGSON3A_R3_1 130 
#define  PRID_REV_LOONGSON3B_R1 129 
#define  PRID_REV_LOONGSON3B_R2 128 
 int PRID_REV_MASK ; 
 int read_c0_prid () ; 

int loongson3_cpu_temp(int cpu)
{
	u32 reg, prid_rev;

	reg = LOONGSON_CHIPTEMP(cpu);
	prid_rev = read_c0_prid() & PRID_REV_MASK;
	switch (prid_rev) {
	case PRID_REV_LOONGSON3A_R1:
		reg = (reg >> 8) & 0xff;
		break;
	case PRID_REV_LOONGSON3B_R1:
	case PRID_REV_LOONGSON3B_R2:
	case PRID_REV_LOONGSON3A_R2_0:
	case PRID_REV_LOONGSON3A_R2_1:
		reg = ((reg >> 8) & 0xff) - 100;
		break;
	case PRID_REV_LOONGSON3A_R3_0:
	case PRID_REV_LOONGSON3A_R3_1:
		reg = (reg & 0xffff)*731/0x4000 - 273;
		break;
	}
	return (int)reg * 1000;
}