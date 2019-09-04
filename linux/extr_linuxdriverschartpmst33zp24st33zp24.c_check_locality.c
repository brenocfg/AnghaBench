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
typedef  int u8 ;
struct tpm_chip {int /*<<< orphan*/  dev; } ;
struct st33zp24_dev {int /*<<< orphan*/  phy_id; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* recv ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  TPM_ACCESS ; 
 int TPM_ACCESS_ACTIVE_LOCALITY ; 
 int TPM_ACCESS_VALID ; 
 struct st33zp24_dev* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static bool check_locality(struct tpm_chip *chip)
{
	struct st33zp24_dev *tpm_dev = dev_get_drvdata(&chip->dev);
	u8 data;
	u8 status;

	status = tpm_dev->ops->recv(tpm_dev->phy_id, TPM_ACCESS, &data, 1);
	if (status && (data &
		(TPM_ACCESS_ACTIVE_LOCALITY | TPM_ACCESS_VALID)) ==
		(TPM_ACCESS_ACTIVE_LOCALITY | TPM_ACCESS_VALID))
		return true;

	return false;
}