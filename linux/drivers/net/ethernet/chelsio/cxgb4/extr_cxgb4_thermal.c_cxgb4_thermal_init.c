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
struct ch_thermal {int trip_temp; int /*<<< orphan*/ * tzdev; int /*<<< orphan*/  trip_type; } ;
struct adapter {int /*<<< orphan*/  pdev_dev; int /*<<< orphan*/  pf; int /*<<< orphan*/  mbox; struct ch_thermal ch_thermal; } ;

/* Variables and functions */
 int CXGB4_NUM_TRIPS ; 
 int /*<<< orphan*/  FW_PARAMS_MNEM_DEV ; 
 int FW_PARAMS_MNEM_V (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FW_PARAMS_PARAM_DEV_DIAG ; 
 int FW_PARAMS_PARAM_X_V (int /*<<< orphan*/ ) ; 
 int FW_PARAMS_PARAM_Y_V (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FW_PARAM_DEV_DIAG_MAXTMPTHRESH ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  THERMAL_TRIP_CRITICAL ; 
 int /*<<< orphan*/  cxgb4_thermal_ops ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int t4_query_params (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int*) ; 
 int /*<<< orphan*/ * thermal_zone_device_register (char*,int,int /*<<< orphan*/ ,struct adapter*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int cxgb4_thermal_init(struct adapter *adap)
{
	struct ch_thermal *ch_thermal = &adap->ch_thermal;
	int num_trip = CXGB4_NUM_TRIPS;
	u32 param, val;
	int ret;

	/* on older firmwares we may not get the trip temperature,
	 * set the num of trips to 0.
	 */
	param = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_DEV) |
		 FW_PARAMS_PARAM_X_V(FW_PARAMS_PARAM_DEV_DIAG) |
		 FW_PARAMS_PARAM_Y_V(FW_PARAM_DEV_DIAG_MAXTMPTHRESH));

	ret = t4_query_params(adap, adap->mbox, adap->pf, 0, 1,
			      &param, &val);
	if (ret < 0) {
		num_trip = 0; /* could not get trip temperature */
	} else {
		ch_thermal->trip_temp = val * 1000;
		ch_thermal->trip_type = THERMAL_TRIP_CRITICAL;
	}

	ch_thermal->tzdev = thermal_zone_device_register("cxgb4", num_trip,
							 0, adap,
							 &cxgb4_thermal_ops,
							 NULL, 0, 0);
	if (IS_ERR(ch_thermal->tzdev)) {
		ret = PTR_ERR(ch_thermal->tzdev);
		dev_err(adap->pdev_dev, "Failed to register thermal zone\n");
		ch_thermal->tzdev = NULL;
		return ret;
	}
	return 0;
}