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
typedef  scalar_t__ u32 ;
struct tpm_chip {int* duration; } ;

/* Variables and functions */
 scalar_t__ TPM2_CC_FIRST ; 
 scalar_t__ TPM2_CC_LAST ; 
 int /*<<< orphan*/  TPM2_DURATION_DEFAULT ; 
 int TPM_UNDEFINED ; 
 int msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int* tpm2_ordinal_duration ; 

unsigned long tpm2_calc_ordinal_duration(struct tpm_chip *chip, u32 ordinal)
{
	int index = TPM_UNDEFINED;
	int duration = 0;

	if (ordinal >= TPM2_CC_FIRST && ordinal <= TPM2_CC_LAST)
		index = tpm2_ordinal_duration[ordinal - TPM2_CC_FIRST];

	if (index != TPM_UNDEFINED)
		duration = chip->duration[index];

	if (duration <= 0)
		duration = msecs_to_jiffies(TPM2_DURATION_DEFAULT);

	return duration;
}