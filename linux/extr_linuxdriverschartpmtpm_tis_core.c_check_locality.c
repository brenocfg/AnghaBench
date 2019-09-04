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
typedef  int u8 ;
struct tpm_tis_data {int locality; } ;
struct tpm_chip {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  TPM_ACCESS (int) ; 
 int TPM_ACCESS_ACTIVE_LOCALITY ; 
 int TPM_ACCESS_VALID ; 
 struct tpm_tis_data* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int tpm_tis_read8 (struct tpm_tis_data*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static bool check_locality(struct tpm_chip *chip, int l)
{
	struct tpm_tis_data *priv = dev_get_drvdata(&chip->dev);
	int rc;
	u8 access;

	rc = tpm_tis_read8(priv, TPM_ACCESS(l), &access);
	if (rc < 0)
		return false;

	if ((access & (TPM_ACCESS_ACTIVE_LOCALITY | TPM_ACCESS_VALID)) ==
	    (TPM_ACCESS_ACTIVE_LOCALITY | TPM_ACCESS_VALID)) {
		priv->locality = l;
		return true;
	}

	return false;
}