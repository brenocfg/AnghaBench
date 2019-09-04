#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u32 ;
struct tpm_chip {int /*<<< orphan*/  dev; int /*<<< orphan*/  timeout_c; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {int /*<<< orphan*/  locality; } ;

/* Variables and functions */
 int EIO ; 
 int ETIME ; 
 int /*<<< orphan*/  SLEEP_DURATION_RESET_HI ; 
 int /*<<< orphan*/  SLEEP_DURATION_RESET_LOW ; 
 size_t TPM_HEADER_SIZE ; 
 int TPM_STS_DATA_AVAIL ; 
 int /*<<< orphan*/  TPM_STS_VALID ; 
 size_t be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int recv_data (struct tpm_chip*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  release_locality (struct tpm_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ tpm_dev ; 
 int /*<<< orphan*/  tpm_tis_i2c_ready (struct tpm_chip*) ; 
 int /*<<< orphan*/  usleep_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_stat (struct tpm_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int tpm_tis_i2c_recv(struct tpm_chip *chip, u8 *buf, size_t count)
{
	int size = 0;
	int status;
	u32 expected;

	if (count < TPM_HEADER_SIZE) {
		size = -EIO;
		goto out;
	}

	/* read first 10 bytes, including tag, paramsize, and result */
	size = recv_data(chip, buf, TPM_HEADER_SIZE);
	if (size < TPM_HEADER_SIZE) {
		dev_err(&chip->dev, "Unable to read header\n");
		goto out;
	}

	expected = be32_to_cpu(*(__be32 *)(buf + 2));
	if (((size_t) expected > count) || (expected < TPM_HEADER_SIZE)) {
		size = -EIO;
		goto out;
	}

	size += recv_data(chip, &buf[TPM_HEADER_SIZE],
			  expected - TPM_HEADER_SIZE);
	if (size < expected) {
		dev_err(&chip->dev, "Unable to read remainder of result\n");
		size = -ETIME;
		goto out;
	}

	wait_for_stat(chip, TPM_STS_VALID, chip->timeout_c, &status);
	if (status & TPM_STS_DATA_AVAIL) {	/* retry? */
		dev_err(&chip->dev, "Error left over data\n");
		size = -EIO;
		goto out;
	}

out:
	tpm_tis_i2c_ready(chip);
	/* The TPM needs some time to clean up here,
	 * so we sleep rather than keeping the bus busy
	 */
	usleep_range(SLEEP_DURATION_RESET_LOW, SLEEP_DURATION_RESET_HI);
	release_locality(chip, tpm_dev.locality, 0);
	return size;
}