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
typedef  int u32 ;
struct vpd_params {int cclk; } ;
struct TYPE_2__ {struct vpd_params vpd; } ;
struct adapter {TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  FW_PARAMS_MNEM_DEV ; 
 int FW_PARAMS_MNEM_V (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FW_PARAMS_PARAM_DEV_CCLK ; 
 int FW_PARAMS_PARAM_X_V (int /*<<< orphan*/ ) ; 
 int t4vf_query_params (struct adapter*,int,int*,int*) ; 

int t4vf_get_vpd_params(struct adapter *adapter)
{
	struct vpd_params *vpd_params = &adapter->params.vpd;
	u32 params[7], vals[7];
	int v;

	params[0] = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_DEV) |
		     FW_PARAMS_PARAM_X_V(FW_PARAMS_PARAM_DEV_CCLK));
	v = t4vf_query_params(adapter, 1, params, vals);
	if (v)
		return v;
	vpd_params->cclk = vals[0];

	return 0;
}