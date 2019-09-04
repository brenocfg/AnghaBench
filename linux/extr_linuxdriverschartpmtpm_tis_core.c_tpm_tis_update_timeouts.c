#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct tpm_tis_data {int dummy; } ;
struct tpm_chip {TYPE_1__* ops; int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {scalar_t__ did_vid; int /*<<< orphan*/  timeout_us; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* clk_enable ) (struct tpm_chip*,int) ;} ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
 int /*<<< orphan*/  TPM_DID_VID (int /*<<< orphan*/ ) ; 
 struct tpm_tis_data* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (unsigned long*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct tpm_chip*,int) ; 
 int /*<<< orphan*/  stub2 (struct tpm_chip*,int) ; 
 int tpm_tis_read32 (struct tpm_tis_data*,int /*<<< orphan*/ ,scalar_t__*) ; 
 TYPE_2__* vendor_timeout_overrides ; 

__attribute__((used)) static bool tpm_tis_update_timeouts(struct tpm_chip *chip,
				    unsigned long *timeout_cap)
{
	struct tpm_tis_data *priv = dev_get_drvdata(&chip->dev);
	int i, rc;
	u32 did_vid;

	if (chip->ops->clk_enable != NULL)
		chip->ops->clk_enable(chip, true);

	rc = tpm_tis_read32(priv, TPM_DID_VID(0), &did_vid);
	if (rc < 0)
		goto out;

	for (i = 0; i != ARRAY_SIZE(vendor_timeout_overrides); i++) {
		if (vendor_timeout_overrides[i].did_vid != did_vid)
			continue;
		memcpy(timeout_cap, vendor_timeout_overrides[i].timeout_us,
		       sizeof(vendor_timeout_overrides[i].timeout_us));
		rc = true;
	}

	rc = false;

out:
	if (chip->ops->clk_enable != NULL)
		chip->ops->clk_enable(chip, false);

	return rc;
}