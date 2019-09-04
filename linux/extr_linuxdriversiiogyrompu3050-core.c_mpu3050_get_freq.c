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
struct mpu3050 {scalar_t__ lpf; int divisor; } ;

/* Variables and functions */
 scalar_t__ MPU3050_DLPF_CFG_256HZ_NOLPF2 ; 

__attribute__((used)) static unsigned int mpu3050_get_freq(struct mpu3050 *mpu3050)
{
	unsigned int freq;

	if (mpu3050->lpf == MPU3050_DLPF_CFG_256HZ_NOLPF2)
		freq = 8000;
	else
		freq = 1000;
	freq /= (mpu3050->divisor + 1);

	return freq;
}