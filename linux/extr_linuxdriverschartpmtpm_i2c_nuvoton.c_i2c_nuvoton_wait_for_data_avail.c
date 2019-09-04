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
typedef  int /*<<< orphan*/  wait_queue_head_t ;
typedef  int /*<<< orphan*/  u32 ;
struct tpm_chip {int dummy; } ;

/* Variables and functions */
 int TPM_STS_DATA_AVAIL ; 
 int TPM_STS_VALID ; 
 int i2c_nuvoton_wait_for_stat (struct tpm_chip*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int i2c_nuvoton_wait_for_data_avail(struct tpm_chip *chip, u32 timeout,
					   wait_queue_head_t *queue)
{
	return i2c_nuvoton_wait_for_stat(chip,
					 TPM_STS_DATA_AVAIL | TPM_STS_VALID,
					 TPM_STS_DATA_AVAIL | TPM_STS_VALID,
					 timeout, queue);
}