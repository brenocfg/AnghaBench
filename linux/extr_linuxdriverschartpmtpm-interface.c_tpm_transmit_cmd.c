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
struct tpm_space {int dummy; } ;
struct tpm_output_header {int /*<<< orphan*/  return_code; } ;
struct tpm_chip {int /*<<< orphan*/  dev; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ EFAULT ; 
 int TPM_ERR_DEACTIVATED ; 
 int TPM_ERR_DISABLED ; 
 scalar_t__ TPM_HEADER_SIZE ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,char const*) ; 
 scalar_t__ tpm_transmit (struct tpm_chip*,struct tpm_space*,void*,size_t,unsigned int) ; 

ssize_t tpm_transmit_cmd(struct tpm_chip *chip, struct tpm_space *space,
			 void *buf, size_t bufsiz,
			 size_t min_rsp_body_length, unsigned int flags,
			 const char *desc)
{
	const struct tpm_output_header *header = buf;
	int err;
	ssize_t len;

	len = tpm_transmit(chip, space, buf, bufsiz, flags);
	if (len <  0)
		return len;

	err = be32_to_cpu(header->return_code);
	if (err != 0 && err != TPM_ERR_DISABLED && err != TPM_ERR_DEACTIVATED
	    && desc)
		dev_err(&chip->dev, "A TPM error (%d) occurred %s\n", err,
			desc);
	if (err)
		return err;

	if (len < min_rsp_body_length + TPM_HEADER_SIZE)
		return -EFAULT;

	return 0;
}