#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct i2c_adapter {int dummy; } ;
struct dvb_frontend_ops {int dummy; } ;
struct dvb_frontend {int /*<<< orphan*/  ops; struct dib7000m_state* demodulator_priv; } ;
struct dib7000m_state {int revision; int /*<<< orphan*/  i2c_addr; struct i2c_adapter* i2c_adap; int /*<<< orphan*/  i2c_master; int /*<<< orphan*/  timf_default; int /*<<< orphan*/  i2c_buffer_lock; struct dvb_frontend demod; int /*<<< orphan*/  cfg; } ;
struct dib7000m_config {TYPE_1__* bw; } ;
struct TYPE_2__ {int /*<<< orphan*/  timf; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIB7000 ; 
 int /*<<< orphan*/  DIB7000MC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dib7000m_demod_reset (struct dib7000m_state*) ; 
 scalar_t__ dib7000m_identify (struct dib7000m_state*) ; 
 struct dib7000m_config dib7000m_ops ; 
 int /*<<< orphan*/  dibx000_init_i2c_master (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct dib7000m_state*) ; 
 struct dib7000m_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct dib7000m_config*,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

struct dvb_frontend * dib7000m_attach(struct i2c_adapter *i2c_adap, u8 i2c_addr, struct dib7000m_config *cfg)
{
	struct dvb_frontend *demod;
	struct dib7000m_state *st;
	st = kzalloc(sizeof(struct dib7000m_state), GFP_KERNEL);
	if (st == NULL)
		return NULL;

	memcpy(&st->cfg, cfg, sizeof(struct dib7000m_config));
	st->i2c_adap = i2c_adap;
	st->i2c_addr = i2c_addr;

	demod                   = &st->demod;
	demod->demodulator_priv = st;
	memcpy(&st->demod.ops, &dib7000m_ops, sizeof(struct dvb_frontend_ops));
	mutex_init(&st->i2c_buffer_lock);

	st->timf_default = cfg->bw->timf;

	if (dib7000m_identify(st) != 0)
		goto error;

	if (st->revision == 0x4000)
		dibx000_init_i2c_master(&st->i2c_master, DIB7000, st->i2c_adap, st->i2c_addr);
	else
		dibx000_init_i2c_master(&st->i2c_master, DIB7000MC, st->i2c_adap, st->i2c_addr);

	dib7000m_demod_reset(st);

	return demod;

error:
	kfree(st);
	return NULL;
}