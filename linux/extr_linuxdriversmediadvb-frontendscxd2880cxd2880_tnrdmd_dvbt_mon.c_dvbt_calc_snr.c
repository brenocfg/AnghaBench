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
struct cxd2880_tnrdmd {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int intlog10 (int) ; 

__attribute__((used)) static int dvbt_calc_snr(struct cxd2880_tnrdmd *tnr_dmd,
			 u32 reg_value, int *snr)
{
	if (!tnr_dmd || !snr)
		return -EINVAL;

	if (reg_value == 0)
		return -EAGAIN;

	if (reg_value > 4996)
		reg_value = 4996;

	*snr = intlog10(reg_value) - intlog10(5350 - reg_value);
	*snr = (*snr + 839) / 1678 + 28500;

	return 0;
}