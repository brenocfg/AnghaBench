#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct tpm_chip {TYPE_1__* active_banks; } ;
struct tpm_buf {int /*<<< orphan*/  data; } ;
struct tpm2_null_auth_area {scalar_t__ auth_size; scalar_t__ attributes; scalar_t__ nonce_size; int /*<<< orphan*/  handle; } ;
struct tpm2_digest {scalar_t__ alg_id; int /*<<< orphan*/  digest; } ;
typedef  int /*<<< orphan*/  auth_area ;
struct TYPE_3__ {scalar_t__ tpm_id; size_t crypto_id; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  TPM2_CC_PCR_EXTEND ; 
 int /*<<< orphan*/  TPM2_RS_PW ; 
 int /*<<< orphan*/  TPM2_ST_SESSIONS ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int* hash_digest_size ; 
 TYPE_1__* tpm2_hash_map ; 
 int /*<<< orphan*/  tpm_buf_append (struct tpm_buf*,unsigned char const*,int) ; 
 int /*<<< orphan*/  tpm_buf_append_u16 (struct tpm_buf*,scalar_t__) ; 
 int /*<<< orphan*/  tpm_buf_append_u32 (struct tpm_buf*,int) ; 
 int /*<<< orphan*/  tpm_buf_destroy (struct tpm_buf*) ; 
 int tpm_buf_init (struct tpm_buf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tpm_transmit_cmd (struct tpm_chip*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

int tpm2_pcr_extend(struct tpm_chip *chip, int pcr_idx, u32 count,
		    struct tpm2_digest *digests)
{
	struct tpm_buf buf;
	struct tpm2_null_auth_area auth_area;
	int rc;
	int i;
	int j;

	if (count > ARRAY_SIZE(chip->active_banks))
		return -EINVAL;

	rc = tpm_buf_init(&buf, TPM2_ST_SESSIONS, TPM2_CC_PCR_EXTEND);
	if (rc)
		return rc;

	tpm_buf_append_u32(&buf, pcr_idx);

	auth_area.handle = cpu_to_be32(TPM2_RS_PW);
	auth_area.nonce_size = 0;
	auth_area.attributes = 0;
	auth_area.auth_size = 0;

	tpm_buf_append_u32(&buf, sizeof(struct tpm2_null_auth_area));
	tpm_buf_append(&buf, (const unsigned char *)&auth_area,
		       sizeof(auth_area));
	tpm_buf_append_u32(&buf, count);

	for (i = 0; i < count; i++) {
		for (j = 0; j < ARRAY_SIZE(tpm2_hash_map); j++) {
			if (digests[i].alg_id != tpm2_hash_map[j].tpm_id)
				continue;
			tpm_buf_append_u16(&buf, digests[i].alg_id);
			tpm_buf_append(&buf, (const unsigned char
					      *)&digests[i].digest,
			       hash_digest_size[tpm2_hash_map[j].crypto_id]);
		}
	}

	rc = tpm_transmit_cmd(chip, NULL, buf.data, PAGE_SIZE, 0, 0,
			      "attempting extend a PCR value");

	tpm_buf_destroy(&buf);

	return rc;
}