#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct pvr2_hdw {TYPE_1__* hdw_desc; } ;
struct pvr2_dvb_props {scalar_t__ (* frontend_attach ) (struct pvr2_dvb_adapter*) ;scalar_t__ (* tuner_attach ) (struct pvr2_dvb_adapter*) ;} ;
struct TYPE_15__ {struct pvr2_hdw* hdw; } ;
struct TYPE_16__ {int mfe_shared; } ;
struct pvr2_dvb_adapter {int /*<<< orphan*/ * i2c_client_demod; int /*<<< orphan*/  i2c_client_tuner; TYPE_4__** fe; TYPE_6__ channel; TYPE_8__ dvb_adap; } ;
struct dvb_tuner_ops {int dummy; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* standby ) (TYPE_4__*) ;} ;
struct TYPE_13__ {void* ts_bus_ctrl; TYPE_2__ analog_ops; int /*<<< orphan*/  tuner_ops; } ;
struct TYPE_14__ {int id; TYPE_3__ ops; int /*<<< orphan*/  tuner_priv; } ;
struct TYPE_11__ {struct pvr2_dvb_props* dvb_props; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int PVR2_CVAL_INPUT_DTV ; 
 int /*<<< orphan*/  PVR2_TRACE_ERROR_LEGS ; 
 int /*<<< orphan*/  PVR2_TRACE_INFO ; 
 int /*<<< orphan*/  dvb_frontend_detach (TYPE_4__*) ; 
 int /*<<< orphan*/  dvb_module_release (int /*<<< orphan*/ ) ; 
 scalar_t__ dvb_register_frontend (TYPE_8__*,TYPE_4__*) ; 
 int /*<<< orphan*/  dvb_unregister_frontend (TYPE_4__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int pvr2_channel_limit_inputs (TYPE_6__*,int) ; 
 void* pvr2_dvb_bus_ctrl ; 
 int /*<<< orphan*/  pvr2_trace (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ stub1 (struct pvr2_dvb_adapter*) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*) ; 
 scalar_t__ stub3 (struct pvr2_dvb_adapter*) ; 
 int /*<<< orphan*/  stub4 (TYPE_4__*) ; 

__attribute__((used)) static int pvr2_dvb_frontend_init(struct pvr2_dvb_adapter *adap)
{
	struct pvr2_hdw *hdw = adap->channel.hdw;
	const struct pvr2_dvb_props *dvb_props = hdw->hdw_desc->dvb_props;
	int ret = 0;

	if (dvb_props == NULL) {
		pvr2_trace(PVR2_TRACE_ERROR_LEGS, "fe_props not defined!");
		return -EINVAL;
	}

	ret = pvr2_channel_limit_inputs(
	    &adap->channel,
	    (1 << PVR2_CVAL_INPUT_DTV));
	if (ret) {
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "failed to grab control of dtv input (code=%d)",
		    ret);
		return ret;
	}

	if (dvb_props->frontend_attach == NULL) {
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "frontend_attach not defined!");
		ret = -EINVAL;
		goto done;
	}

	if (dvb_props->frontend_attach(adap) == 0 && adap->fe[0]) {
		if (dvb_register_frontend(&adap->dvb_adap, adap->fe[0])) {
			pvr2_trace(PVR2_TRACE_ERROR_LEGS,
				   "frontend registration failed!");
			ret = -ENODEV;
			goto fail_frontend0;
		}
		if (adap->fe[0]->ops.analog_ops.standby)
			adap->fe[0]->ops.analog_ops.standby(adap->fe[0]);

		pvr2_trace(PVR2_TRACE_INFO, "transferring fe[%d] ts_bus_ctrl() to pvr2_dvb_bus_ctrl()",
			   adap->fe[0]->id);
		adap->fe[0]->ops.ts_bus_ctrl = pvr2_dvb_bus_ctrl;
	} else {
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "no frontend was attached!");
		ret = -ENODEV;
		return ret;
	}

	if (dvb_props->tuner_attach && dvb_props->tuner_attach(adap)) {
		pvr2_trace(PVR2_TRACE_ERROR_LEGS, "tuner attach failed");
		ret = -ENODEV;
		goto fail_tuner;
	}

	if (adap->fe[1]) {
		adap->fe[1]->id = 1;
		adap->fe[1]->tuner_priv = adap->fe[0]->tuner_priv;
		memcpy(&adap->fe[1]->ops.tuner_ops,
		       &adap->fe[0]->ops.tuner_ops,
		       sizeof(struct dvb_tuner_ops));

		if (dvb_register_frontend(&adap->dvb_adap, adap->fe[1])) {
			pvr2_trace(PVR2_TRACE_ERROR_LEGS,
				   "frontend registration failed!");
			ret = -ENODEV;
			goto fail_frontend1;
		}
		/* MFE lock */
		adap->dvb_adap.mfe_shared = 1;

		if (adap->fe[1]->ops.analog_ops.standby)
			adap->fe[1]->ops.analog_ops.standby(adap->fe[1]);

		pvr2_trace(PVR2_TRACE_INFO, "transferring fe[%d] ts_bus_ctrl() to pvr2_dvb_bus_ctrl()",
			   adap->fe[1]->id);
		adap->fe[1]->ops.ts_bus_ctrl = pvr2_dvb_bus_ctrl;
	}
done:
	pvr2_channel_limit_inputs(&adap->channel, 0);
	return ret;

fail_frontend1:
	dvb_frontend_detach(adap->fe[1]);
	adap->fe[1] = NULL;
fail_tuner:
	dvb_unregister_frontend(adap->fe[0]);
fail_frontend0:
	dvb_frontend_detach(adap->fe[0]);
	adap->fe[0] = NULL;
	dvb_module_release(adap->i2c_client_tuner);
	dvb_module_release(adap->i2c_client_demod[1]);
	dvb_module_release(adap->i2c_client_demod[0]);

	return ret;
}