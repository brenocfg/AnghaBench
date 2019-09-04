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
typedef  int /*<<< orphan*/  u8 ;
struct i2c_adapter {int dummy; } ;
struct dvb_frontend_ops {int dummy; } ;
struct dvb_frontend {int /*<<< orphan*/  ops; struct dib3000mc_state* demodulator_priv; } ;
struct dib3000mc_state {int /*<<< orphan*/  i2c_addr; struct i2c_adapter* i2c_adap; int /*<<< orphan*/  i2c_master; struct dvb_frontend demod; struct dib3000mc_config* cfg; } ;
struct dib3000mc_config {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIB3000MC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ dib3000mc_identify (struct dib3000mc_state*) ; 
 int /*<<< orphan*/  dib3000mc_ops ; 
 int /*<<< orphan*/  dib3000mc_write_word (struct dib3000mc_state*,int,int) ; 
 int /*<<< orphan*/  dibx000_init_i2c_master (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct dib3000mc_state*) ; 
 struct dib3000mc_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

struct dvb_frontend * dib3000mc_attach(struct i2c_adapter *i2c_adap, u8 i2c_addr, struct dib3000mc_config *cfg)
{
	struct dvb_frontend *demod;
	struct dib3000mc_state *st;
	st = kzalloc(sizeof(struct dib3000mc_state), GFP_KERNEL);
	if (st == NULL)
		return NULL;

	st->cfg = cfg;
	st->i2c_adap = i2c_adap;
	st->i2c_addr = i2c_addr;

	demod                   = &st->demod;
	demod->demodulator_priv = st;
	memcpy(&st->demod.ops, &dib3000mc_ops, sizeof(struct dvb_frontend_ops));

	if (dib3000mc_identify(st) != 0)
		goto error;

	dibx000_init_i2c_master(&st->i2c_master, DIB3000MC, st->i2c_adap, st->i2c_addr);

	dib3000mc_write_word(st, 1037, 0x3130);

	return demod;

error:
	kfree(st);
	return NULL;
}