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
typedef  int u32 ;
struct vpd_params {int cclk; } ;
struct adapter {int /*<<< orphan*/  pf; int /*<<< orphan*/  mbox; } ;

/* Variables and functions */
 int /*<<< orphan*/  FW_PARAMS_MNEM_DEV ; 
 int FW_PARAMS_MNEM_V (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FW_PARAMS_PARAM_DEV_CCLK ; 
 int FW_PARAMS_PARAM_X_V (int /*<<< orphan*/ ) ; 
 int t4_get_raw_vpd_params (struct adapter*,struct vpd_params*) ; 
 int t4_query_params (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int*) ; 

int t4_get_vpd_params(struct adapter *adapter, struct vpd_params *p)
{
	u32 cclk_param, cclk_val;
	int ret;

	/* Grab the raw VPD parameters.
	 */
	ret = t4_get_raw_vpd_params(adapter, p);
	if (ret)
		return ret;

	/* Ask firmware for the Core Clock since it knows how to translate the
	 * Reference Clock ('V2') VPD field into a Core Clock value ...
	 */
	cclk_param = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_DEV) |
		      FW_PARAMS_PARAM_X_V(FW_PARAMS_PARAM_DEV_CCLK));
	ret = t4_query_params(adapter, adapter->mbox, adapter->pf, 0,
			      1, &cclk_param, &cclk_val);

	if (ret)
		return ret;
	p->cclk = cclk_val;

	return 0;
}