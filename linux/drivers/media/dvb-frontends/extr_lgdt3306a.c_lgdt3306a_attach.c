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
typedef  int u8 ;
struct dvb_frontend {struct lgdt3306a_state* demodulator_priv; int /*<<< orphan*/  ops; } ;
struct lgdt3306a_state {int current_frequency; int current_modulation; struct dvb_frontend frontend; struct i2c_adapter* i2c_adap; struct lgdt3306a_config const* cfg; } ;
struct lgdt3306a_config {int /*<<< orphan*/  i2c_addr; } ;
struct i2c_adapter {int dummy; } ;
struct dvb_frontend_ops {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dbg_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_adapter_id (struct i2c_adapter*) ; 
 int /*<<< orphan*/  kfree (struct lgdt3306a_state*) ; 
 struct lgdt3306a_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ lg_chkerr (int) ; 
 int /*<<< orphan*/  lgdt3306a_ops ; 
 int lgdt3306a_read_reg (struct lgdt3306a_state*,int,int*) ; 
 int /*<<< orphan*/  lgdt3306a_sleep (struct lgdt3306a_state*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pr_warn (char*,...) ; 

struct dvb_frontend *lgdt3306a_attach(const struct lgdt3306a_config *config,
				      struct i2c_adapter *i2c_adap)
{
	struct lgdt3306a_state *state = NULL;
	int ret;
	u8 val;

	dbg_info("(%d-%04x)\n",
	       i2c_adap ? i2c_adapter_id(i2c_adap) : 0,
	       config ? config->i2c_addr : 0);

	state = kzalloc(sizeof(struct lgdt3306a_state), GFP_KERNEL);
	if (state == NULL)
		goto fail;

	state->cfg = config;
	state->i2c_adap = i2c_adap;

	memcpy(&state->frontend.ops, &lgdt3306a_ops,
	       sizeof(struct dvb_frontend_ops));
	state->frontend.demodulator_priv = state;

	/* verify that we're talking to a lg3306a */
	/* FGR - NOTE - there is no obvious ChipId to check; we check
	 * some "known" bits after reset, but it's still just a guess */
	ret = lgdt3306a_read_reg(state, 0x0000, &val);
	if (lg_chkerr(ret))
		goto fail;
	if ((val & 0x74) != 0x74) {
		pr_warn("expected 0x74, got 0x%x\n", (val & 0x74));
#if 0
		/* FIXME - re-enable when we know this is right */
		goto fail;
#endif
	}
	ret = lgdt3306a_read_reg(state, 0x0001, &val);
	if (lg_chkerr(ret))
		goto fail;
	if ((val & 0xf6) != 0xc6) {
		pr_warn("expected 0xc6, got 0x%x\n", (val & 0xf6));
#if 0
		/* FIXME - re-enable when we know this is right */
		goto fail;
#endif
	}
	ret = lgdt3306a_read_reg(state, 0x0002, &val);
	if (lg_chkerr(ret))
		goto fail;
	if ((val & 0x73) != 0x03) {
		pr_warn("expected 0x03, got 0x%x\n", (val & 0x73));
#if 0
		/* FIXME - re-enable when we know this is right */
		goto fail;
#endif
	}

	state->current_frequency = -1;
	state->current_modulation = -1;

	lgdt3306a_sleep(state);

	return &state->frontend;

fail:
	pr_warn("unable to detect LGDT3306A hardware\n");
	kfree(state);
	return NULL;
}