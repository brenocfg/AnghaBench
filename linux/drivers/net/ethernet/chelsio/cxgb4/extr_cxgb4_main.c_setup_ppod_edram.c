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
struct adapter {int /*<<< orphan*/  pdev_dev; int /*<<< orphan*/  pf; int /*<<< orphan*/  mbox; } ;

/* Variables and functions */
 int /*<<< orphan*/  FW_PARAMS_MNEM_DEV ; 
 unsigned int FW_PARAMS_MNEM_V (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FW_PARAMS_PARAM_DEV_PPOD_EDRAM ; 
 unsigned int FW_PARAMS_PARAM_X_V (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int t4_query_params (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int*,unsigned int*) ; 
 int t4_set_params (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int*,unsigned int*) ; 

__attribute__((used)) static int setup_ppod_edram(struct adapter *adap)
{
	unsigned int param, val;
	int ret;

	/* Driver sends FW_PARAMS_PARAM_DEV_PPOD_EDRAM read command to check
	 * if firmware supports ppod edram feature or not. If firmware
	 * returns 1, then driver can enable this feature by sending
	 * FW_PARAMS_PARAM_DEV_PPOD_EDRAM write command with value 1 to
	 * enable ppod edram feature.
	 */
	param = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_DEV) |
		FW_PARAMS_PARAM_X_V(FW_PARAMS_PARAM_DEV_PPOD_EDRAM));

	ret = t4_query_params(adap, adap->mbox, adap->pf, 0, 1, &param, &val);
	if (ret < 0) {
		dev_warn(adap->pdev_dev,
			 "querying PPOD_EDRAM support failed: %d\n",
			 ret);
		return -1;
	}

	if (val != 1)
		return -1;

	ret = t4_set_params(adap, adap->mbox, adap->pf, 0, 1, &param, &val);
	if (ret < 0) {
		dev_err(adap->pdev_dev,
			"setting PPOD_EDRAM failed: %d\n", ret);
		return -1;
	}
	return 0;
}