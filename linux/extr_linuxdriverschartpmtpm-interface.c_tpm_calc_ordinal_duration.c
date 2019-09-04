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
typedef  size_t u32 ;
struct tpm_chip {int* duration; } ;

/* Variables and functions */
 int HZ ; 
 size_t TPM_MAX_ORDINAL ; 
 int TPM_UNDEFINED ; 
 int* tpm_ordinal_duration ; 

unsigned long tpm_calc_ordinal_duration(struct tpm_chip *chip,
					   u32 ordinal)
{
	int duration_idx = TPM_UNDEFINED;
	int duration = 0;

	/*
	 * We only have a duration table for protected commands, where the upper
	 * 16 bits are 0. For the few other ordinals the fallback will be used.
	 */
	if (ordinal < TPM_MAX_ORDINAL)
		duration_idx = tpm_ordinal_duration[ordinal];

	if (duration_idx != TPM_UNDEFINED)
		duration = chip->duration[duration_idx];
	if (duration <= 0)
		return 2 * 60 * HZ;
	else
		return duration;
}