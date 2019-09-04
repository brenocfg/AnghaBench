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
typedef  int /*<<< orphan*/  u32 ;
struct trusted_key_payload {int dummy; } ;
struct trusted_key_options {int dummy; } ;
struct tpm_chip {int /*<<< orphan*/  tpm_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  TPM_TRANSMIT_UNLOCKED ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tpm2_flush_context_cmd (struct tpm_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tpm2_load_cmd (struct tpm_chip*,struct trusted_key_payload*,struct trusted_key_options*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int tpm2_unseal_cmd (struct tpm_chip*,struct trusted_key_payload*,struct trusted_key_options*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int tpm2_unseal_trusted(struct tpm_chip *chip,
			struct trusted_key_payload *payload,
			struct trusted_key_options *options)
{
	u32 blob_handle;
	int rc;

	mutex_lock(&chip->tpm_mutex);
	rc = tpm2_load_cmd(chip, payload, options, &blob_handle,
			   TPM_TRANSMIT_UNLOCKED);
	if (rc)
		goto out;

	rc = tpm2_unseal_cmd(chip, payload, options, blob_handle,
			     TPM_TRANSMIT_UNLOCKED);
	tpm2_flush_context_cmd(chip, blob_handle, TPM_TRANSMIT_UNLOCKED);
out:
	mutex_unlock(&chip->tpm_mutex);
	return rc;
}