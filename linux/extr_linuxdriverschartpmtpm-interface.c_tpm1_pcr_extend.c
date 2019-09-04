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
struct tpm_chip {int dummy; } ;
struct tpm_buf {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXTEND_PCR_RESULT_BODY_SIZE ; 
 int /*<<< orphan*/  EXTEND_PCR_RESULT_SIZE ; 
 int /*<<< orphan*/  TPM_DIGEST_SIZE ; 
 int /*<<< orphan*/  TPM_ORD_PCR_EXTEND ; 
 int /*<<< orphan*/  TPM_TAG_RQU_COMMAND ; 
 int /*<<< orphan*/  tpm_buf_append (struct tpm_buf*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tpm_buf_append_u32 (struct tpm_buf*,int) ; 
 int /*<<< orphan*/  tpm_buf_destroy (struct tpm_buf*) ; 
 int tpm_buf_init (struct tpm_buf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tpm_transmit_cmd (struct tpm_chip*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int tpm1_pcr_extend(struct tpm_chip *chip, int pcr_idx, const u8 *hash,
			   char *log_msg)
{
	struct tpm_buf buf;
	int rc;

	rc = tpm_buf_init(&buf, TPM_TAG_RQU_COMMAND, TPM_ORD_PCR_EXTEND);
	if (rc)
		return rc;

	tpm_buf_append_u32(&buf, pcr_idx);
	tpm_buf_append(&buf, hash, TPM_DIGEST_SIZE);

	rc = tpm_transmit_cmd(chip, NULL, buf.data, EXTEND_PCR_RESULT_SIZE,
			      EXTEND_PCR_RESULT_BODY_SIZE, 0, log_msg);
	tpm_buf_destroy(&buf);
	return rc;
}