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
typedef  int u16 ;
struct adapter {int /*<<< orphan*/  pf; int /*<<< orphan*/  mbox; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  FW_PARAMS_MNEM_DEV ; 
 int FW_PARAMS_MNEM_V (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FW_PARAMS_PARAM_DEV_DBQ_TIMER ; 
 int FW_PARAMS_PARAM_X_V (int /*<<< orphan*/ ) ; 
 int FW_PARAMS_PARAM_Y_V (int) ; 
 int t4_query_params (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int*) ; 

int t4_read_sge_dbqtimers(struct adapter *adap, unsigned int ndbqtimers,
			  u16 *dbqtimers)
{
	int ret, dbqtimerix;

	ret = 0;
	dbqtimerix = 0;
	while (dbqtimerix < ndbqtimers) {
		int nparams, param;
		u32 params[7], vals[7];

		nparams = ndbqtimers - dbqtimerix;
		if (nparams > ARRAY_SIZE(params))
			nparams = ARRAY_SIZE(params);

		for (param = 0; param < nparams; param++)
			params[param] =
			  (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_DEV) |
			   FW_PARAMS_PARAM_X_V(FW_PARAMS_PARAM_DEV_DBQ_TIMER) |
			   FW_PARAMS_PARAM_Y_V(dbqtimerix + param));
		ret = t4_query_params(adap, adap->mbox, adap->pf, 0,
				      nparams, params, vals);
		if (ret)
			break;

		for (param = 0; param < nparams; param++)
			dbqtimers[dbqtimerix++] = vals[param];
	}
	return ret;
}