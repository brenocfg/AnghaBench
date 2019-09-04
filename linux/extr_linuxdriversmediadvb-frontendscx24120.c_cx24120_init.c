#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_14__ ;
typedef  struct TYPE_18__   TYPE_13__ ;
typedef  struct TYPE_17__   TYPE_12__ ;
typedef  struct TYPE_16__   TYPE_11__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
typedef  int u8 ;
struct firmware {int size; int* data; } ;
struct TYPE_19__ {int len; TYPE_13__* stat; } ;
struct TYPE_17__ {int len; TYPE_11__* stat; } ;
struct TYPE_15__ {int len; TYPE_9__* stat; } ;
struct TYPE_27__ {int len; TYPE_7__* stat; } ;
struct TYPE_25__ {int len; TYPE_5__* stat; } ;
struct TYPE_23__ {int len; TYPE_3__* stat; } ;
struct dtv_frontend_properties {TYPE_14__ block_count; TYPE_12__ block_error; TYPE_10__ post_bit_count; TYPE_8__ post_bit_error; TYPE_6__ cnr; TYPE_4__ strength; } ;
struct dvb_frontend {struct cx24120_state* demodulator_priv; struct dtv_frontend_properties dtv_property_cache; } ;
struct cx24120_state {int cold_init; TYPE_2__* i2c; TYPE_1__* config; } ;
struct cx24120_cmd {int len; int* arg; int /*<<< orphan*/  id; } ;
struct TYPE_28__ {void* scale; } ;
struct TYPE_26__ {void* scale; } ;
struct TYPE_24__ {void* scale; } ;
struct TYPE_22__ {void* scale; } ;
struct TYPE_21__ {int /*<<< orphan*/  dev; } ;
struct TYPE_20__ {int (* request_firmware ) (struct dvb_frontend*,struct firmware const**,int /*<<< orphan*/ ) ;} ;
struct TYPE_18__ {void* scale; } ;
struct TYPE_16__ {void* scale; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_BANDWIDTH ; 
 int /*<<< orphan*/  CMD_BER_CTRL ; 
 int /*<<< orphan*/  CMD_FWVERSION ; 
 int /*<<< orphan*/  CMD_START_TUNER ; 
 void* CX24120_BER_WINDOW ; 
 int /*<<< orphan*/  CX24120_FIRMWARE ; 
 int CX24120_REG_MAILBOX ; 
 int EREMOTEIO ; 
 void* FE_SCALE_NOT_AVAILABLE ; 
 int cx24120_message_send (struct cx24120_state*,struct cx24120_cmd*) ; 
 scalar_t__ cx24120_msg_mpeg_output_config (struct cx24120_state*,int) ; 
 scalar_t__ cx24120_msg_mpeg_output_global_config (struct cx24120_state*,int /*<<< orphan*/ ) ; 
 int cx24120_readreg (struct cx24120_state*,int) ; 
 int cx24120_set_vco (struct cx24120_state*) ; 
 int /*<<< orphan*/  cx24120_test_rom (struct cx24120_state*) ; 
 int /*<<< orphan*/  cx24120_writereg (struct cx24120_state*,int,int) ; 
 int /*<<< orphan*/  cx24120_writeregs (struct cx24120_state*,int,int*,int,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  err (char*,...) ; 
 int /*<<< orphan*/  info (char*,unsigned char,unsigned char,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int stub1 (struct dvb_frontend*,struct firmware const**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cx24120_init(struct dvb_frontend *fe)
{
	const struct firmware *fw;
	struct dtv_frontend_properties *c = &fe->dtv_property_cache;
	struct cx24120_state *state = fe->demodulator_priv;
	struct cx24120_cmd cmd;
	u8 reg;
	int ret, i;
	unsigned char vers[4];

	if (state->cold_init)
		return 0;

	/* ???? */
	cx24120_writereg(state, 0xea, 0x00);
	cx24120_test_rom(state);
	reg = cx24120_readreg(state, 0xfb) & 0xfe;
	cx24120_writereg(state, 0xfb, reg);
	reg = cx24120_readreg(state, 0xfc) & 0xfe;
	cx24120_writereg(state, 0xfc, reg);
	cx24120_writereg(state, 0xc3, 0x04);
	cx24120_writereg(state, 0xc4, 0x04);
	cx24120_writereg(state, 0xce, 0x00);
	cx24120_writereg(state, 0xcf, 0x00);
	reg = cx24120_readreg(state, 0xea) & 0xfe;
	cx24120_writereg(state, 0xea, reg);
	cx24120_writereg(state, 0xeb, 0x0c);
	cx24120_writereg(state, 0xec, 0x06);
	cx24120_writereg(state, 0xed, 0x05);
	cx24120_writereg(state, 0xee, 0x03);
	cx24120_writereg(state, 0xef, 0x05);
	cx24120_writereg(state, 0xf3, 0x03);
	cx24120_writereg(state, 0xf4, 0x44);

	for (i = 0; i < 3; i++) {
		cx24120_writereg(state, 0xf0 + i, 0x04);
		cx24120_writereg(state, 0xe6 + i, 0x02);
	}

	cx24120_writereg(state, 0xea, (reg | 0x01));
	for (i = 0; i < 6; i += 2) {
		cx24120_writereg(state, 0xc5 + i, 0x00);
		cx24120_writereg(state, 0xc6 + i, 0x00);
	}

	cx24120_writereg(state, 0xe4, 0x03);
	cx24120_writereg(state, 0xeb, 0x0a);

	dev_dbg(&state->i2c->dev, "requesting firmware (%s) to download...\n",
		CX24120_FIRMWARE);

	ret = state->config->request_firmware(fe, &fw, CX24120_FIRMWARE);
	if (ret) {
		err("Could not load firmware (%s): %d\n", CX24120_FIRMWARE,
		    ret);
		return ret;
	}

	dev_dbg(&state->i2c->dev,
		"Firmware found, size %d bytes (%02x %02x .. %02x %02x)\n",
		(int)fw->size,			/* firmware_size in bytes */
		fw->data[0],			/* fw 1st byte */
		fw->data[1],			/* fw 2d byte */
		fw->data[fw->size - 2],		/* fw before last byte */
		fw->data[fw->size - 1]);	/* fw last byte */

	cx24120_test_rom(state);
	reg = cx24120_readreg(state, 0xfb) & 0xfe;
	cx24120_writereg(state, 0xfb, reg);
	cx24120_writereg(state, 0xe0, 0x76);
	cx24120_writereg(state, 0xf7, 0x81);
	cx24120_writereg(state, 0xf8, 0x00);
	cx24120_writereg(state, 0xf9, 0x00);
	cx24120_writeregs(state, 0xfa, fw->data, (fw->size - 1), 0x00);
	cx24120_writereg(state, 0xf7, 0xc0);
	cx24120_writereg(state, 0xe0, 0x00);
	reg = (fw->size - 2) & 0x00ff;
	cx24120_writereg(state, 0xf8, reg);
	reg = ((fw->size - 2) >> 8) & 0x00ff;
	cx24120_writereg(state, 0xf9, reg);
	cx24120_writereg(state, 0xf7, 0x00);
	cx24120_writereg(state, 0xdc, 0x00);
	cx24120_writereg(state, 0xdc, 0x07);
	msleep(500);

	/* Check final byte matches final byte of firmware */
	reg = cx24120_readreg(state, 0xe1);
	if (reg == fw->data[fw->size - 1]) {
		dev_dbg(&state->i2c->dev, "Firmware uploaded successfully\n");
		ret = 0;
	} else {
		err("Firmware upload failed. Last byte returned=0x%x\n", ret);
		ret = -EREMOTEIO;
	}
	cx24120_writereg(state, 0xdc, 0x00);
	release_firmware(fw);
	if (ret != 0)
		return ret;

	/* Start tuner */
	cmd.id = CMD_START_TUNER;
	cmd.len = 3;
	cmd.arg[0] = 0x00;
	cmd.arg[1] = 0x00;
	cmd.arg[2] = 0x00;

	if (cx24120_message_send(state, &cmd) != 0) {
		err("Error tuner start! :(\n");
		return -EREMOTEIO;
	}

	/* Set VCO */
	ret = cx24120_set_vco(state);
	if (ret != 0) {
		err("Error set VCO! :(\n");
		return ret;
	}

	/* set bandwidth */
	cmd.id = CMD_BANDWIDTH;
	cmd.len = 12;
	cmd.arg[0] = 0x00;
	cmd.arg[1] = 0x00;
	cmd.arg[2] = 0x00;
	cmd.arg[3] = 0x00;
	cmd.arg[4] = 0x05;
	cmd.arg[5] = 0x02;
	cmd.arg[6] = 0x02;
	cmd.arg[7] = 0x00;
	cmd.arg[8] = 0x05;
	cmd.arg[9] = 0x02;
	cmd.arg[10] = 0x02;
	cmd.arg[11] = 0x00;

	if (cx24120_message_send(state, &cmd)) {
		err("Error set bandwidth!\n");
		return -EREMOTEIO;
	}

	reg = cx24120_readreg(state, 0xba);
	if (reg > 3) {
		dev_dbg(&state->i2c->dev, "Reset-readreg 0xba: %x\n", ret);
		err("Error initialising tuner!\n");
		return -EREMOTEIO;
	}

	dev_dbg(&state->i2c->dev, "Tuner initialised correctly.\n");

	/* Initialise mpeg outputs */
	cx24120_writereg(state, 0xeb, 0x0a);
	if (cx24120_msg_mpeg_output_global_config(state, 0) ||
	    cx24120_msg_mpeg_output_config(state, 0) ||
	    cx24120_msg_mpeg_output_config(state, 1) ||
	    cx24120_msg_mpeg_output_config(state, 2)) {
		err("Error initialising mpeg output. :(\n");
		return -EREMOTEIO;
	}

	/* Set size of BER window */
	cmd.id = CMD_BER_CTRL;
	cmd.len = 3;
	cmd.arg[0] = 0x00;
	cmd.arg[1] = CX24120_BER_WINDOW;
	cmd.arg[2] = CX24120_BER_WINDOW;
	if (cx24120_message_send(state, &cmd)) {
		err("Error setting ber window\n");
		return -EREMOTEIO;
	}

	/* Firmware CMD 35: Get firmware version */
	cmd.id = CMD_FWVERSION;
	cmd.len = 1;
	for (i = 0; i < 4; i++) {
		cmd.arg[0] = i;
		ret = cx24120_message_send(state, &cmd);
		if (ret != 0)
			return ret;
		vers[i] = cx24120_readreg(state, CX24120_REG_MAILBOX);
	}
	info("FW version %i.%i.%i.%i\n", vers[0], vers[1], vers[2], vers[3]);

	/* init stats here in order signal app which stats are supported */
	c->strength.len = 1;
	c->strength.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->cnr.len = 1;
	c->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->post_bit_error.len = 1;
	c->post_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->post_bit_count.len = 1;
	c->post_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->block_error.len = 1;
	c->block_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->block_count.len = 1;
	c->block_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;

	state->cold_init = 1;

	return 0;
}