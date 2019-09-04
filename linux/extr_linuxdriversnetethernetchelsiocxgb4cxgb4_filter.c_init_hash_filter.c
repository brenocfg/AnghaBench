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
struct TYPE_2__ {int hash_filter; int /*<<< orphan*/  chip; } ;
struct adapter {int /*<<< orphan*/  pdev_dev; TYPE_1__ params; } ;

/* Variables and functions */
 int EINVAL ; 
 int HASH_ACTV_HIT_G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LE_DB_RSP_CODE_0_A ; 
 int /*<<< orphan*/  LE_DB_RSP_CODE_1_A ; 
 int TCAM_ACTV_HIT_G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ is_t6 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 

int init_hash_filter(struct adapter *adap)
{
	/* On T6, verify the necessary register configs and warn the user in
	 * case of improper config
	 */
	if (is_t6(adap->params.chip)) {
		if (TCAM_ACTV_HIT_G(t4_read_reg(adap, LE_DB_RSP_CODE_0_A)) != 4)
			goto err;

		if (HASH_ACTV_HIT_G(t4_read_reg(adap, LE_DB_RSP_CODE_1_A)) != 4)
			goto err;
	} else {
		dev_err(adap->pdev_dev, "Hash filter supported only on T6\n");
		return -EINVAL;
	}
	adap->params.hash_filter = 1;
	return 0;
err:
	dev_warn(adap->pdev_dev, "Invalid hash filter config!\n");
	return -EINVAL;
}