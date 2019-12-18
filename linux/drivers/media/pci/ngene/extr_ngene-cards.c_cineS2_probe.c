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
struct stv090x_config {int /*<<< orphan*/  address; } ;
struct ngene_channel {int number; int demod_type; TYPE_3__* dev; } ;
struct i2c_msg {int* buf; int len; int /*<<< orphan*/  addr; int /*<<< orphan*/  flags; } ;
struct i2c_adapter {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_6__ {TYPE_2__* card_info; TYPE_1__* pci_dev; } ;
struct TYPE_5__ {struct stv090x_config** fe_config; } ;
struct TYPE_4__ {struct device dev; } ;

/* Variables and functions */
 int DEMOD_TYPE_DRXK ; 
#define  DEMOD_TYPE_SONY_C2T2 134 
#define  DEMOD_TYPE_SONY_C2T2I 133 
#define  DEMOD_TYPE_SONY_CT2 132 
#define  DEMOD_TYPE_SONY_ISDBT 131 
 int DEMOD_TYPE_STV0367 ; 
 int DEMOD_TYPE_STV090X ; 
#define  DEMOD_TYPE_STV0910 130 
 int /*<<< orphan*/  DEMOD_TYPE_XO2 ; 
 int EIO ; 
 int ENODEV ; 
#define  NGENE_XO2_TYPE_CI 129 
#define  NGENE_XO2_TYPE_DUOFLEX 128 
 int /*<<< orphan*/  demod_attach_cxd28xx (struct ngene_channel*,struct i2c_adapter*,int) ; 
 int /*<<< orphan*/  demod_attach_drxk (struct ngene_channel*,struct i2c_adapter*) ; 
 int /*<<< orphan*/  demod_attach_stv0367 (struct ngene_channel*,struct i2c_adapter*) ; 
 int demod_attach_stv0900 (struct ngene_channel*) ; 
 int /*<<< orphan*/  demod_attach_stv0910 (struct ngene_channel*,struct i2c_adapter*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,...) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int) ; 
 struct i2c_adapter* i2c_adapter_from_chan (struct ngene_channel*) ; 
 int i2c_transfer (struct i2c_adapter*,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  init_xo2 (struct ngene_channel*,struct i2c_adapter*) ; 
 scalar_t__ port_has_drxk (struct i2c_adapter*,int) ; 
 scalar_t__ port_has_stv0367 (struct i2c_adapter*) ; 
 scalar_t__ port_has_stv0900 (struct i2c_adapter*,int) ; 
 scalar_t__ port_has_xo2 (struct i2c_adapter*,int*,int*) ; 
 int /*<<< orphan*/ * xo2names ; 

__attribute__((used)) static int cineS2_probe(struct ngene_channel *chan)
{
	struct device *pdev = &chan->dev->pci_dev->dev;
	struct i2c_adapter *i2c = i2c_adapter_from_chan(chan);
	struct stv090x_config *fe_conf;
	u8 buf[3];
	u8 xo2_type, xo2_id, xo2_demodtype;
	u8 sony_osc24 = 0;
	struct i2c_msg i2c_msg = { .flags = 0, .buf = buf };
	int rc;

	if (port_has_xo2(i2c, &xo2_type, &xo2_id)) {
		xo2_id >>= 2;
		dev_dbg(pdev, "XO2 on channel %d (type %d, id %d)\n",
			chan->number, xo2_type, xo2_id);

		switch (xo2_type) {
		case NGENE_XO2_TYPE_DUOFLEX:
			if (chan->number & 1)
				dev_dbg(pdev,
					"skipping XO2 init on odd channel %d",
					chan->number);
			else
				init_xo2(chan, i2c);

			xo2_demodtype = DEMOD_TYPE_XO2 + xo2_id;

			switch (xo2_demodtype) {
			case DEMOD_TYPE_SONY_CT2:
			case DEMOD_TYPE_SONY_ISDBT:
			case DEMOD_TYPE_SONY_C2T2:
			case DEMOD_TYPE_SONY_C2T2I:
				dev_info(pdev, "%s (XO2) on channel %d\n",
					 xo2names[xo2_id], chan->number);
				chan->demod_type = xo2_demodtype;
				if (xo2_demodtype == DEMOD_TYPE_SONY_C2T2I)
					sony_osc24 = 1;

				demod_attach_cxd28xx(chan, i2c, sony_osc24);
				break;
			case DEMOD_TYPE_STV0910:
				dev_info(pdev, "%s (XO2) on channel %d\n",
					 xo2names[xo2_id], chan->number);
				chan->demod_type = xo2_demodtype;
				demod_attach_stv0910(chan, i2c);
				break;
			default:
				dev_warn(pdev,
					 "Unsupported XO2 module on channel %d\n",
					 chan->number);
				return -ENODEV;
			}
			break;
		case NGENE_XO2_TYPE_CI:
			dev_info(pdev, "DuoFlex CI modules not supported\n");
			return -ENODEV;
		default:
			dev_info(pdev, "Unsupported XO2 module type\n");
			return -ENODEV;
		}
	} else if (port_has_stv0900(i2c, chan->number)) {
		chan->demod_type = DEMOD_TYPE_STV090X;
		fe_conf = chan->dev->card_info->fe_config[chan->number];
		/* demod found, attach it */
		rc = demod_attach_stv0900(chan);
		if (rc < 0 || chan->number < 2)
			return rc;

		/* demod #2: reprogram outputs DPN1 & DPN2 */
		i2c_msg.addr = fe_conf->address;
		i2c_msg.len = 3;
		buf[0] = 0xf1;
		switch (chan->number) {
		case 2:
			buf[1] = 0x5c;
			buf[2] = 0xc2;
			break;
		case 3:
			buf[1] = 0x61;
			buf[2] = 0xcc;
			break;
		default:
			return -ENODEV;
		}
		rc = i2c_transfer(i2c, &i2c_msg, 1);
		if (rc != 1) {
			dev_err(pdev, "Could not setup DPNx\n");
			return -EIO;
		}
	} else if (port_has_drxk(i2c, chan->number^2)) {
		chan->demod_type = DEMOD_TYPE_DRXK;
		demod_attach_drxk(chan, i2c);
	} else if (port_has_stv0367(i2c)) {
		chan->demod_type = DEMOD_TYPE_STV0367;
		dev_info(pdev, "STV0367 on channel %d\n", chan->number);
		demod_attach_stv0367(chan, i2c);
	} else {
		dev_info(pdev, "No demod found on chan %d\n", chan->number);
		return -ENODEV;
	}
	return 0;
}