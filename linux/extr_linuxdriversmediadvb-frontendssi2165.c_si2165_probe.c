#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_9__ {int /*<<< orphan*/  name; } ;
struct TYPE_11__ {TYPE_2__ info; int /*<<< orphan*/ * delsys; int /*<<< orphan*/ * release; } ;
struct TYPE_10__ {TYPE_4__ ops; struct si2165_state* demodulator_priv; } ;
struct TYPE_8__ {scalar_t__ chip_mode; int ref_freq_hz; int /*<<< orphan*/  inversion; int /*<<< orphan*/  i2c_addr; } ;
struct si2165_state {scalar_t__ chip_revcode; scalar_t__ chip_type; int has_dvbt; int has_dvbc; TYPE_3__ fe; struct i2c_client* client; TYPE_1__ config; int /*<<< orphan*/  regmap; } ;
struct si2165_platform_data {scalar_t__ chip_mode; int ref_freq_hz; TYPE_3__** fe; int /*<<< orphan*/  inversion; } ;
struct regmap_config {int reg_bits; int val_bits; int max_register; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_12__ {struct si2165_platform_data* platform_data; } ;
struct i2c_client {TYPE_5__ dev; int /*<<< orphan*/  addr; } ;
struct dvb_frontend_ops {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_CHIP_MODE ; 
 int /*<<< orphan*/  REG_CHIP_REVCODE ; 
 int /*<<< orphan*/  REV_CHIP_TYPE ; 
 scalar_t__ SI2165_MODE_OFF ; 
 int /*<<< orphan*/  SYS_DVBC_ANNEX_A ; 
 int /*<<< orphan*/  SYS_DVBT ; 
 int /*<<< orphan*/  dev_dbg (TYPE_5__*,char*,int) ; 
 int /*<<< orphan*/  dev_err (TYPE_5__*,char*,int,...) ; 
 int /*<<< orphan*/  dev_info (TYPE_5__*,char*,char const*,char,int,char) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,struct regmap_config const*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct si2165_state*) ; 
 int /*<<< orphan*/  kfree (struct si2165_state*) ; 
 struct si2165_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_4__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  si2165_ops ; 
 int si2165_readreg8 (struct si2165_state*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int si2165_writereg8 (struct si2165_state*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  strlcat (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static int si2165_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	struct si2165_state *state = NULL;
	struct si2165_platform_data *pdata = client->dev.platform_data;
	int n;
	int ret = 0;
	u8 val;
	char rev_char;
	const char *chip_name;
	static const struct regmap_config regmap_config = {
		.reg_bits = 16,
		.val_bits = 8,
		.max_register = 0x08ff,
	};

	/* allocate memory for the internal state */
	state = kzalloc(sizeof(*state), GFP_KERNEL);
	if (!state) {
		ret = -ENOMEM;
		goto error;
	}

	/* create regmap */
	state->regmap = devm_regmap_init_i2c(client, &regmap_config);
	if (IS_ERR(state->regmap)) {
		ret = PTR_ERR(state->regmap);
		goto error;
	}

	/* setup the state */
	state->client = client;
	state->config.i2c_addr = client->addr;
	state->config.chip_mode = pdata->chip_mode;
	state->config.ref_freq_hz = pdata->ref_freq_hz;
	state->config.inversion = pdata->inversion;

	if (state->config.ref_freq_hz < 4000000 ||
	    state->config.ref_freq_hz > 27000000) {
		dev_err(&state->client->dev, "ref_freq of %d Hz not supported by this driver\n",
			state->config.ref_freq_hz);
		ret = -EINVAL;
		goto error;
	}

	/* create dvb_frontend */
	memcpy(&state->fe.ops, &si2165_ops,
	       sizeof(struct dvb_frontend_ops));
	state->fe.ops.release = NULL;
	state->fe.demodulator_priv = state;
	i2c_set_clientdata(client, state);

	/* powerup */
	ret = si2165_writereg8(state, REG_CHIP_MODE, state->config.chip_mode);
	if (ret < 0)
		goto nodev_error;

	ret = si2165_readreg8(state, REG_CHIP_MODE, &val);
	if (ret < 0)
		goto nodev_error;
	if (val != state->config.chip_mode)
		goto nodev_error;

	ret = si2165_readreg8(state, REG_CHIP_REVCODE, &state->chip_revcode);
	if (ret < 0)
		goto nodev_error;

	ret = si2165_readreg8(state, REV_CHIP_TYPE, &state->chip_type);
	if (ret < 0)
		goto nodev_error;

	/* powerdown */
	ret = si2165_writereg8(state, REG_CHIP_MODE, SI2165_MODE_OFF);
	if (ret < 0)
		goto nodev_error;

	if (state->chip_revcode < 26)
		rev_char = 'A' + state->chip_revcode;
	else
		rev_char = '?';

	switch (state->chip_type) {
	case 0x06:
		chip_name = "Si2161";
		state->has_dvbt = true;
		break;
	case 0x07:
		chip_name = "Si2165";
		state->has_dvbt = true;
		state->has_dvbc = true;
		break;
	default:
		dev_err(&state->client->dev, "Unsupported Silicon Labs chip (type %d, rev %d)\n",
			state->chip_type, state->chip_revcode);
		goto nodev_error;
	}

	dev_info(&state->client->dev,
		 "Detected Silicon Labs %s-%c (type %d, rev %d)\n",
		chip_name, rev_char, state->chip_type,
		state->chip_revcode);

	strlcat(state->fe.ops.info.name, chip_name,
		sizeof(state->fe.ops.info.name));

	n = 0;
	if (state->has_dvbt) {
		state->fe.ops.delsys[n++] = SYS_DVBT;
		strlcat(state->fe.ops.info.name, " DVB-T",
			sizeof(state->fe.ops.info.name));
	}
	if (state->has_dvbc) {
		state->fe.ops.delsys[n++] = SYS_DVBC_ANNEX_A;
		strlcat(state->fe.ops.info.name, " DVB-C",
			sizeof(state->fe.ops.info.name));
	}

	/* return fe pointer */
	*pdata->fe = &state->fe;

	return 0;

nodev_error:
	ret = -ENODEV;
error:
	kfree(state);
	dev_dbg(&client->dev, "failed=%d\n", ret);
	return ret;
}