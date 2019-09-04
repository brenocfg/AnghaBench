#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  size_t u32 ;
struct ddb_port {size_t lnr; char* name; char* type_name; scalar_t__ nr; void* class; TYPE_2__* i2c; scalar_t__ type; struct ddb* dev; } ;
struct TYPE_4__ {int device; } ;
struct ddb_link {TYPE_3__* info; TYPE_1__ ids; } ;
struct ddb {int /*<<< orphan*/  dev; struct ddb_link* link; } ;
struct TYPE_6__ {scalar_t__ type; int i2c_mask; scalar_t__ mci_ports; int ts_quirks; scalar_t__ mci_type; } ;
struct TYPE_5__ {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ DDB_CI_EXTERNAL_SONY ; 
 scalar_t__ DDB_CI_EXTERNAL_XO2 ; 
 scalar_t__ DDB_CI_INTERNAL ; 
 scalar_t__ DDB_OCTOPUS_CI ; 
 scalar_t__ DDB_OCTOPUS_MAX ; 
 scalar_t__ DDB_OCTOPUS_MCI ; 
 void* DDB_PORT_CI ; 
 void* DDB_PORT_LOOP ; 
 void* DDB_PORT_NONE ; 
 void* DDB_PORT_TUNER ; 
 scalar_t__ DDB_TUNER_DUMMY ; 
 scalar_t__ DDB_TUNER_DVBC2T2I_SONY_P ; 
 scalar_t__ DDB_TUNER_DVBC2T2_SONY_P ; 
 scalar_t__ DDB_TUNER_DVBCT2_SONY_P ; 
 scalar_t__ DDB_TUNER_DVBCT_ST ; 
 scalar_t__ DDB_TUNER_DVBCT_TR ; 
 scalar_t__ DDB_TUNER_DVBS_ST ; 
 scalar_t__ DDB_TUNER_DVBS_STV0910_P ; 
 scalar_t__ DDB_TUNER_DVBS_STV0910_PR ; 
 scalar_t__ DDB_TUNER_DVBS_ST_AA ; 
 scalar_t__ DDB_TUNER_ISDBT_SONY_P ; 
 scalar_t__ DDB_TUNER_MCI ; 
 scalar_t__ DDB_TUNER_MXL5XX ; 
 scalar_t__ DDB_TUNER_XO2 ; 
 int /*<<< orphan*/  I2C_SPEED_100 ; 
 int /*<<< orphan*/  I2C_SPEED_400 ; 
 scalar_t__ I2C_TIMING ; 
 int TS_QUIRK_REVERSED ; 
 int /*<<< orphan*/  ddbwritel (struct ddb*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ dummy_tuner ; 
 int /*<<< orphan*/  init_xo2 (struct ddb_port*) ; 
 int /*<<< orphan*/  init_xo2_ci (struct ddb_port*) ; 
 scalar_t__ port_has_cxd (struct ddb_port*,int*) ; 
 scalar_t__ port_has_cxd28xx (struct ddb_port*,int*) ; 
 scalar_t__ port_has_drxks (struct ddb_port*) ; 
 scalar_t__ port_has_encti (struct ddb_port*) ; 
 scalar_t__ port_has_stv0367 (struct ddb_port*) ; 
 scalar_t__ port_has_stv0900 (struct ddb_port*) ; 
 scalar_t__ port_has_stv0900_aa (struct ddb_port*,int*) ; 
 scalar_t__ port_has_xo2 (struct ddb_port*,int*,int*) ; 
 scalar_t__ ts_loop ; 
 char** xo2names ; 
 char** xo2types ; 

__attribute__((used)) static void ddb_port_probe(struct ddb_port *port)
{
	struct ddb *dev = port->dev;
	u32 l = port->lnr;
	struct ddb_link *link = &dev->link[l];
	u8 id, type;

	port->name = "NO MODULE";
	port->type_name = "NONE";
	port->class = DDB_PORT_NONE;

	/* Handle missing ports and ports without I2C */

	if (dummy_tuner && !port->nr &&
	    link->ids.device == 0x0005) {
		port->name = "DUMMY";
		port->class = DDB_PORT_TUNER;
		port->type = DDB_TUNER_DUMMY;
		port->type_name = "DUMMY";
		return;
	}

	if (port->nr == ts_loop) {
		port->name = "TS LOOP";
		port->class = DDB_PORT_LOOP;
		return;
	}

	if (port->nr == 1 && link->info->type == DDB_OCTOPUS_CI &&
	    link->info->i2c_mask == 1) {
		port->name = "NO TAB";
		port->class = DDB_PORT_NONE;
		return;
	}

	if (link->info->type == DDB_OCTOPUS_MAX) {
		port->name = "DUAL DVB-S2 MAX";
		port->type_name = "MXL5XX";
		port->class = DDB_PORT_TUNER;
		port->type = DDB_TUNER_MXL5XX;
		if (port->i2c)
			ddbwritel(dev, I2C_SPEED_400,
				  port->i2c->regs + I2C_TIMING);
		return;
	}

	if (link->info->type == DDB_OCTOPUS_MCI) {
		if (port->nr >= link->info->mci_ports)
			return;
		port->name = "DUAL MCI";
		port->type_name = "MCI";
		port->class = DDB_PORT_TUNER;
		port->type = DDB_TUNER_MCI + link->info->mci_type;
		return;
	}

	if (port->nr > 1 && link->info->type == DDB_OCTOPUS_CI) {
		port->name = "CI internal";
		port->type_name = "INTERNAL";
		port->class = DDB_PORT_CI;
		port->type = DDB_CI_INTERNAL;
	}

	if (!port->i2c)
		return;

	/* Probe ports with I2C */

	if (port_has_cxd(port, &id)) {
		if (id == 1) {
			port->name = "CI";
			port->type_name = "CXD2099";
			port->class = DDB_PORT_CI;
			port->type = DDB_CI_EXTERNAL_SONY;
			ddbwritel(dev, I2C_SPEED_400,
				  port->i2c->regs + I2C_TIMING);
		} else {
			dev_info(dev->dev, "Port %d: Uninitialized DuoFlex\n",
				 port->nr);
			return;
		}
	} else if (port_has_xo2(port, &type, &id)) {
		ddbwritel(dev, I2C_SPEED_400, port->i2c->regs + I2C_TIMING);
		/*dev_info(dev->dev, "XO2 ID %02x\n", id);*/
		if (type == 2) {
			port->name = "DuoFlex CI";
			port->class = DDB_PORT_CI;
			port->type = DDB_CI_EXTERNAL_XO2;
			port->type_name = "CI_XO2";
			init_xo2_ci(port);
			return;
		}
		id >>= 2;
		if (id > 5) {
			port->name = "unknown XO2 DuoFlex";
			port->type_name = "UNKNOWN";
		} else {
			port->name = xo2names[id];
			port->class = DDB_PORT_TUNER;
			port->type = DDB_TUNER_XO2 + id;
			port->type_name = xo2types[id];
			init_xo2(port);
		}
	} else if (port_has_cxd28xx(port, &id)) {
		switch (id) {
		case 0xa4:
			port->name = "DUAL DVB-C2T2 CXD2843";
			port->type = DDB_TUNER_DVBC2T2_SONY_P;
			port->type_name = "DVBC2T2_SONY";
			break;
		case 0xb1:
			port->name = "DUAL DVB-CT2 CXD2837";
			port->type = DDB_TUNER_DVBCT2_SONY_P;
			port->type_name = "DVBCT2_SONY";
			break;
		case 0xb0:
			port->name = "DUAL ISDB-T CXD2838";
			port->type = DDB_TUNER_ISDBT_SONY_P;
			port->type_name = "ISDBT_SONY";
			break;
		case 0xc1:
			port->name = "DUAL DVB-C2T2 ISDB-T CXD2854";
			port->type = DDB_TUNER_DVBC2T2I_SONY_P;
			port->type_name = "DVBC2T2I_ISDBT_SONY";
			break;
		default:
			return;
		}
		port->class = DDB_PORT_TUNER;
		ddbwritel(dev, I2C_SPEED_400, port->i2c->regs + I2C_TIMING);
	} else if (port_has_stv0900(port)) {
		port->name = "DUAL DVB-S2";
		port->class = DDB_PORT_TUNER;
		port->type = DDB_TUNER_DVBS_ST;
		port->type_name = "DVBS_ST";
		ddbwritel(dev, I2C_SPEED_100, port->i2c->regs + I2C_TIMING);
	} else if (port_has_stv0900_aa(port, &id)) {
		port->name = "DUAL DVB-S2";
		port->class = DDB_PORT_TUNER;
		if (id == 0x51) {
			if (port->nr == 0 &&
			    link->info->ts_quirks & TS_QUIRK_REVERSED)
				port->type = DDB_TUNER_DVBS_STV0910_PR;
			else
				port->type = DDB_TUNER_DVBS_STV0910_P;
			port->type_name = "DVBS_ST_0910";
		} else {
			port->type = DDB_TUNER_DVBS_ST_AA;
			port->type_name = "DVBS_ST_AA";
		}
		ddbwritel(dev, I2C_SPEED_100, port->i2c->regs + I2C_TIMING);
	} else if (port_has_drxks(port)) {
		port->name = "DUAL DVB-C/T";
		port->class = DDB_PORT_TUNER;
		port->type = DDB_TUNER_DVBCT_TR;
		port->type_name = "DVBCT_TR";
		ddbwritel(dev, I2C_SPEED_400, port->i2c->regs + I2C_TIMING);
	} else if (port_has_stv0367(port)) {
		port->name = "DUAL DVB-C/T";
		port->class = DDB_PORT_TUNER;
		port->type = DDB_TUNER_DVBCT_ST;
		port->type_name = "DVBCT_ST";
		ddbwritel(dev, I2C_SPEED_100, port->i2c->regs + I2C_TIMING);
	} else if (port_has_encti(port)) {
		port->name = "ENCTI";
		port->class = DDB_PORT_LOOP;
	}
}