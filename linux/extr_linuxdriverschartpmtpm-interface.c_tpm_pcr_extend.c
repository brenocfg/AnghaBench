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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct tpm_chip {scalar_t__* active_banks; int flags; } ;
struct tpm2_digest {scalar_t__ alg_id; int /*<<< orphan*/  digest; } ;
typedef  int /*<<< orphan*/  digest_list ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 int ENODEV ; 
 scalar_t__ TPM2_ALG_ERROR ; 
 int TPM_CHIP_FLAG_TPM2 ; 
 int /*<<< orphan*/  TPM_DIGEST_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct tpm2_digest*,int /*<<< orphan*/ ,int) ; 
 int tpm1_pcr_extend (struct tpm_chip*,int,int /*<<< orphan*/  const*,char*) ; 
 int tpm2_pcr_extend (struct tpm_chip*,int,scalar_t__,struct tpm2_digest*) ; 
 struct tpm_chip* tpm_find_get_ops (struct tpm_chip*) ; 
 int /*<<< orphan*/  tpm_put_ops (struct tpm_chip*) ; 

int tpm_pcr_extend(struct tpm_chip *chip, int pcr_idx, const u8 *hash)
{
	int rc;
	struct tpm2_digest digest_list[ARRAY_SIZE(chip->active_banks)];
	u32 count = 0;
	int i;

	chip = tpm_find_get_ops(chip);
	if (!chip)
		return -ENODEV;

	if (chip->flags & TPM_CHIP_FLAG_TPM2) {
		memset(digest_list, 0, sizeof(digest_list));

		for (i = 0; i < ARRAY_SIZE(chip->active_banks) &&
			    chip->active_banks[i] != TPM2_ALG_ERROR; i++) {
			digest_list[i].alg_id = chip->active_banks[i];
			memcpy(digest_list[i].digest, hash, TPM_DIGEST_SIZE);
			count++;
		}

		rc = tpm2_pcr_extend(chip, pcr_idx, count, digest_list);
		tpm_put_ops(chip);
		return rc;
	}

	rc = tpm1_pcr_extend(chip, pcr_idx, hash,
			     "attempting extend a PCR value");
	tpm_put_ops(chip);
	return rc;
}