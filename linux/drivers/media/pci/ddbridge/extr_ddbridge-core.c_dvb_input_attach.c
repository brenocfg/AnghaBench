#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_15__ ;
typedef  struct TYPE_16__   TYPE_11__ ;

/* Type definitions */
struct dvb_tuner_ops {int dummy; } ;
struct TYPE_22__ {int capabilities; int (* connect_frontend ) (TYPE_5__*,TYPE_6__*) ;int /*<<< orphan*/  (* add_frontend ) (TYPE_5__*,TYPE_6__*) ;} ;
struct dvb_demux {int filternum; int feednum; TYPE_5__ dmx; int /*<<< orphan*/  stop_feed; int /*<<< orphan*/  start_feed; struct ddb_input* priv; } ;
struct dvb_adapter {int dummy; } ;
struct ddb_port {size_t lnr; scalar_t__ nr; int type; TYPE_4__* dev; struct ddb_dvb* dvb; } ;
struct ddb_input {int nr; struct ddb_port* port; } ;
struct ddb_ids {int hwid; } ;
struct TYPE_17__ {int filternum; TYPE_5__* demux; } ;
struct TYPE_23__ {int /*<<< orphan*/  source; } ;
struct ddb_dvb {int attached; TYPE_11__* fe; TYPE_11__* fe2; TYPE_15__ dmxdev; int /*<<< orphan*/  dvbnet; TYPE_6__ hw_frontend; struct dvb_demux demux; TYPE_6__ mem_frontend; struct dvb_adapter* adap; } ;
struct TYPE_21__ {int /*<<< orphan*/  dev; TYPE_3__* link; } ;
struct TYPE_20__ {TYPE_1__* info; struct ddb_ids ids; } ;
struct TYPE_19__ {int /*<<< orphan*/  tuner_ops; } ;
struct TYPE_18__ {int ts_quirks; } ;
struct TYPE_16__ {TYPE_2__ ops; int /*<<< orphan*/  tuner_priv; } ;

/* Variables and functions */
#define  DDB_TUNER_DUMMY 145 
#define  DDB_TUNER_DVBC2T2I_SONY 144 
#define  DDB_TUNER_DVBC2T2I_SONY_P 143 
#define  DDB_TUNER_DVBC2T2_SONY 142 
#define  DDB_TUNER_DVBC2T2_SONY_P 141 
#define  DDB_TUNER_DVBCT2_SONY 140 
#define  DDB_TUNER_DVBCT2_SONY_P 139 
#define  DDB_TUNER_DVBCT_ST 138 
#define  DDB_TUNER_DVBCT_TR 137 
#define  DDB_TUNER_DVBS_ST 136 
#define  DDB_TUNER_DVBS_STV0910 135 
#define  DDB_TUNER_DVBS_STV0910_P 134 
#define  DDB_TUNER_DVBS_STV0910_PR 133 
#define  DDB_TUNER_DVBS_ST_AA 132 
#define  DDB_TUNER_ISDBT_SONY 131 
#define  DDB_TUNER_ISDBT_SONY_P 130 
#define  DDB_TUNER_MCI_SX8 129 
#define  DDB_TUNER_MXL5XX 128 
 int /*<<< orphan*/  DMX_FRONTEND_0 ; 
 int DMX_MEMORY_BASED_FILTERING ; 
 int /*<<< orphan*/  DMX_MEMORY_FE ; 
 int DMX_SECTION_FILTERING ; 
 int DMX_TS_FILTERING ; 
 int ENODEV ; 
 int TS_QUIRK_ALT_OSC ; 
 int TS_QUIRK_SERIAL ; 
 int /*<<< orphan*/  ddb_fe_attach_mci (struct ddb_input*,int) ; 
 int /*<<< orphan*/  ddb_fe_attach_mxl5xx (struct ddb_input*) ; 
 int /*<<< orphan*/  demod_attach_cxd28xx (struct ddb_input*,int,int) ; 
 int /*<<< orphan*/  demod_attach_drxk (struct ddb_input*) ; 
 int /*<<< orphan*/  demod_attach_dummy (struct ddb_input*) ; 
 int /*<<< orphan*/  demod_attach_stv0367 (struct ddb_input*) ; 
 int /*<<< orphan*/  demod_attach_stv0900 (struct ddb_input*,int) ; 
 int /*<<< orphan*/  demod_attach_stv0910 (struct ddb_input*,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int dvb_dmx_init (struct dvb_demux*) ; 
 int dvb_dmxdev_init (TYPE_15__*,struct dvb_adapter*) ; 
 int /*<<< orphan*/  dvb_frontend_detach (TYPE_11__*) ; 
 int /*<<< orphan*/  dvb_input_detach (struct ddb_input*) ; 
 int dvb_net_init (struct dvb_adapter*,int /*<<< orphan*/ *,TYPE_5__*) ; 
 scalar_t__ dvb_register_frontend (struct dvb_adapter*,TYPE_11__*) ; 
 int /*<<< orphan*/  dvb_unregister_frontend (TYPE_11__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  start_feed ; 
 int /*<<< orphan*/  stop_feed ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,TYPE_6__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_5__*,TYPE_6__*) ; 
 int stub3 (TYPE_5__*,TYPE_6__*) ; 
 int /*<<< orphan*/  tuner_attach_stv6110 (struct ddb_input*,int) ; 
 int /*<<< orphan*/  tuner_attach_stv6111 (struct ddb_input*,int) ; 
 int /*<<< orphan*/  tuner_attach_tda18212 (struct ddb_input*,int) ; 
 int /*<<< orphan*/  tuner_attach_tda18271 (struct ddb_input*) ; 

__attribute__((used)) static int dvb_input_attach(struct ddb_input *input)
{
	int ret = 0;
	struct ddb_dvb *dvb = &input->port->dvb[input->nr & 1];
	struct ddb_port *port = input->port;
	struct dvb_adapter *adap = dvb->adap;
	struct dvb_demux *dvbdemux = &dvb->demux;
	struct ddb_ids *devids = &input->port->dev->link[input->port->lnr].ids;
	int par = 0, osc24 = 0, tsfast = 0;

	/*
	 * Determine if bridges with stv0910 demods can run with fast TS and
	 * thus support high bandwidth transponders.
	 * STV0910_PR and STV0910_P tuner types covers all relevant bridges,
	 * namely the CineS2 V7(A) and the Octopus CI S2 Pro/Advanced. All
	 * DuoFlex S2 V4(A) have type=DDB_TUNER_DVBS_STV0910 without any suffix
	 * and are limited by the serial link to the bridge, thus won't work
	 * in fast TS mode.
	 */
	if (port->nr == 0 &&
	    (port->type == DDB_TUNER_DVBS_STV0910_PR ||
	     port->type == DDB_TUNER_DVBS_STV0910_P)) {
		/* fast TS on port 0 requires FPGA version >= 1.7 */
		if ((devids->hwid & 0x00ffffff) >= 0x00010007)
			tsfast = 1;
	}

	dvb->attached = 0x01;

	dvbdemux->priv = input;
	dvbdemux->dmx.capabilities = DMX_TS_FILTERING |
		DMX_SECTION_FILTERING | DMX_MEMORY_BASED_FILTERING;
	dvbdemux->start_feed = start_feed;
	dvbdemux->stop_feed = stop_feed;
	dvbdemux->filternum = 256;
	dvbdemux->feednum = 256;
	ret = dvb_dmx_init(dvbdemux);
	if (ret < 0)
		return ret;
	dvb->attached = 0x10;

	dvb->dmxdev.filternum = 256;
	dvb->dmxdev.demux = &dvbdemux->dmx;
	ret = dvb_dmxdev_init(&dvb->dmxdev, adap);
	if (ret < 0)
		goto err_detach;
	dvb->attached = 0x11;

	dvb->mem_frontend.source = DMX_MEMORY_FE;
	dvb->demux.dmx.add_frontend(&dvb->demux.dmx, &dvb->mem_frontend);
	dvb->hw_frontend.source = DMX_FRONTEND_0;
	dvb->demux.dmx.add_frontend(&dvb->demux.dmx, &dvb->hw_frontend);
	ret = dvbdemux->dmx.connect_frontend(&dvbdemux->dmx, &dvb->hw_frontend);
	if (ret < 0)
		goto err_detach;
	dvb->attached = 0x12;

	ret = dvb_net_init(adap, &dvb->dvbnet, dvb->dmxdev.demux);
	if (ret < 0)
		goto err_detach;
	dvb->attached = 0x20;

	dvb->fe = NULL;
	dvb->fe2 = NULL;
	switch (port->type) {
	case DDB_TUNER_MXL5XX:
		if (ddb_fe_attach_mxl5xx(input) < 0)
			goto err_detach;
		break;
	case DDB_TUNER_DVBS_ST:
		if (demod_attach_stv0900(input, 0) < 0)
			goto err_detach;
		if (tuner_attach_stv6110(input, 0) < 0)
			goto err_tuner;
		break;
	case DDB_TUNER_DVBS_ST_AA:
		if (demod_attach_stv0900(input, 1) < 0)
			goto err_detach;
		if (tuner_attach_stv6110(input, 1) < 0)
			goto err_tuner;
		break;
	case DDB_TUNER_DVBS_STV0910:
		if (demod_attach_stv0910(input, 0, tsfast) < 0)
			goto err_detach;
		if (tuner_attach_stv6111(input, 0) < 0)
			goto err_tuner;
		break;
	case DDB_TUNER_DVBS_STV0910_PR:
		if (demod_attach_stv0910(input, 1, tsfast) < 0)
			goto err_detach;
		if (tuner_attach_stv6111(input, 1) < 0)
			goto err_tuner;
		break;
	case DDB_TUNER_DVBS_STV0910_P:
		if (demod_attach_stv0910(input, 0, tsfast) < 0)
			goto err_detach;
		if (tuner_attach_stv6111(input, 1) < 0)
			goto err_tuner;
		break;
	case DDB_TUNER_DVBCT_TR:
		if (demod_attach_drxk(input) < 0)
			goto err_detach;
		if (tuner_attach_tda18271(input) < 0)
			goto err_tuner;
		break;
	case DDB_TUNER_DVBCT_ST:
		if (demod_attach_stv0367(input) < 0)
			goto err_detach;
		if (tuner_attach_tda18212(input, port->type) < 0)
			goto err_tuner;
		break;
	case DDB_TUNER_DVBC2T2I_SONY_P:
		if (input->port->dev->link[input->port->lnr].info->ts_quirks &
		    TS_QUIRK_ALT_OSC)
			osc24 = 0;
		else
			osc24 = 1;
		/* fall-through */
	case DDB_TUNER_DVBCT2_SONY_P:
	case DDB_TUNER_DVBC2T2_SONY_P:
	case DDB_TUNER_ISDBT_SONY_P:
		if (input->port->dev->link[input->port->lnr].info->ts_quirks
			& TS_QUIRK_SERIAL)
			par = 0;
		else
			par = 1;
		if (demod_attach_cxd28xx(input, par, osc24) < 0)
			goto err_detach;
		if (tuner_attach_tda18212(input, port->type) < 0)
			goto err_tuner;
		break;
	case DDB_TUNER_DVBC2T2I_SONY:
		osc24 = 1;
		/* fall-through */
	case DDB_TUNER_DVBCT2_SONY:
	case DDB_TUNER_DVBC2T2_SONY:
	case DDB_TUNER_ISDBT_SONY:
		if (demod_attach_cxd28xx(input, 0, osc24) < 0)
			goto err_detach;
		if (tuner_attach_tda18212(input, port->type) < 0)
			goto err_tuner;
		break;
	case DDB_TUNER_DUMMY:
		if (demod_attach_dummy(input) < 0)
			goto err_detach;
		break;
	case DDB_TUNER_MCI_SX8:
		if (ddb_fe_attach_mci(input, port->type) < 0)
			goto err_detach;
		break;
	default:
		return 0;
	}
	dvb->attached = 0x30;

	if (dvb->fe) {
		if (dvb_register_frontend(adap, dvb->fe) < 0)
			goto err_detach;

		if (dvb->fe2) {
			if (dvb_register_frontend(adap, dvb->fe2) < 0) {
				dvb_unregister_frontend(dvb->fe);
				goto err_detach;
			}
			dvb->fe2->tuner_priv = dvb->fe->tuner_priv;
			memcpy(&dvb->fe2->ops.tuner_ops,
			       &dvb->fe->ops.tuner_ops,
			       sizeof(struct dvb_tuner_ops));
		}
	}

	dvb->attached = 0x31;
	return 0;

err_tuner:
	dev_err(port->dev->dev, "tuner attach failed!\n");

	if (dvb->fe2)
		dvb_frontend_detach(dvb->fe2);
	if (dvb->fe)
		dvb_frontend_detach(dvb->fe);
err_detach:
	dvb_input_detach(input);

	/* return error from ret if set */
	if (ret < 0)
		return ret;

	return -ENODEV;
}