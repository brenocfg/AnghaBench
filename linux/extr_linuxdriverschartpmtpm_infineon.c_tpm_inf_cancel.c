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
struct tpm_chip {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void tpm_inf_cancel(struct tpm_chip *chip)
{
	/*
	   Since we are using the legacy mode to communicate
	   with the TPM, we have no cancel functions, but have
	   a workaround for interrupting the TPM through WTX.
	 */
}