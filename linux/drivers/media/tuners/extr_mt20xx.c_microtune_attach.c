#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_9__ {char* name; struct i2c_adapter* adap; int /*<<< orphan*/  addr; } ;
struct microtune_priv {TYPE_4__ i2c_props; } ;
struct i2c_adapter {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct TYPE_7__ {TYPE_1__ info; } ;
struct TYPE_8__ {TYPE_2__ tuner_ops; } ;
struct dvb_frontend {TYPE_3__ ops; struct microtune_priv* tuner_priv; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 unsigned char ARRAY_SIZE (char**) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  MT2032 129 
#define  MT2050 128 
 scalar_t__ debug ; 
 struct microtune_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 char** microtune_part ; 
 int /*<<< orphan*/  mt2032_init (struct dvb_frontend*) ; 
 int /*<<< orphan*/  mt2050_init (struct dvb_frontend*) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  tuner_dbg (char*,int,unsigned char*) ; 
 int /*<<< orphan*/  tuner_i2c_xfer_recv (TYPE_4__*,unsigned char*,int) ; 
 int /*<<< orphan*/  tuner_i2c_xfer_send (TYPE_4__*,unsigned char*,int) ; 
 int /*<<< orphan*/  tuner_info (char*,...) ; 

struct dvb_frontend *microtune_attach(struct dvb_frontend *fe,
				      struct i2c_adapter* i2c_adap,
				      u8 i2c_addr)
{
	struct microtune_priv *priv = NULL;
	char *name;
	unsigned char buf[21];
	int company_code;

	priv = kzalloc(sizeof(struct microtune_priv), GFP_KERNEL);
	if (priv == NULL)
		return NULL;
	fe->tuner_priv = priv;

	priv->i2c_props.addr = i2c_addr;
	priv->i2c_props.adap = i2c_adap;
	priv->i2c_props.name = "mt20xx";

	//priv->radio_if2 = 10700 * 1000;	/* 10.7MHz - FM radio */

	memset(buf,0,sizeof(buf));

	name = "unknown";

	tuner_i2c_xfer_send(&priv->i2c_props,buf,1);
	tuner_i2c_xfer_recv(&priv->i2c_props,buf,21);
	if (debug)
		tuner_dbg("MT20xx hexdump: %*ph\n", 21, buf);

	company_code = buf[0x11] << 8 | buf[0x12];
	tuner_info("microtune: companycode=%04x part=%02x rev=%02x\n",
		   company_code,buf[0x13],buf[0x14]);


	if (buf[0x13] < ARRAY_SIZE(microtune_part) &&
	    NULL != microtune_part[buf[0x13]])
		name = microtune_part[buf[0x13]];
	switch (buf[0x13]) {
	case MT2032:
		mt2032_init(fe);
		break;
	case MT2050:
		mt2050_init(fe);
		break;
	default:
		tuner_info("microtune %s found, not (yet?) supported, sorry :-/\n",
			   name);
		return NULL;
	}

	strscpy(fe->ops.tuner_ops.info.name, name,
		sizeof(fe->ops.tuner_ops.info.name));
	tuner_info("microtune %s found, OK\n",name);
	return fe;
}