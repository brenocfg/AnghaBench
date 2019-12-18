#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct i2c_adapter {int dummy; } ;
struct dvb_frontend_ops {int dummy; } ;
struct dvb_frontend {struct bcm3510_state* demodulator_priv; int /*<<< orphan*/  ops; } ;
struct bcm3510_state {struct dvb_frontend frontend; int /*<<< orphan*/  hab_mutex; struct i2c_adapter* i2c; struct bcm3510_config const* config; } ;
struct bcm3510_config {int dummy; } ;
struct TYPE_4__ {int REV; int LAYER; } ;
struct TYPE_5__ {TYPE_1__ REVID_e0; } ;
typedef  TYPE_2__ bcm3510_register_value ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  bcm3510_ops ; 
 int bcm3510_readB (struct bcm3510_state*,int,TYPE_2__*) ; 
 int /*<<< orphan*/  bcm3510_reset (struct bcm3510_state*) ; 
 int /*<<< orphan*/  deb_info (char*,int,int) ; 
 int /*<<< orphan*/  info (char*,int,int) ; 
 int /*<<< orphan*/  kfree (struct bcm3510_state*) ; 
 struct bcm3510_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

struct dvb_frontend* bcm3510_attach(const struct bcm3510_config *config,
				   struct i2c_adapter *i2c)
{
	struct bcm3510_state* state = NULL;
	int ret;
	bcm3510_register_value v;

	/* allocate memory for the internal state */
	state = kzalloc(sizeof(struct bcm3510_state), GFP_KERNEL);
	if (state == NULL)
		goto error;

	/* setup the state */

	state->config = config;
	state->i2c = i2c;

	/* create dvb_frontend */
	memcpy(&state->frontend.ops, &bcm3510_ops, sizeof(struct dvb_frontend_ops));
	state->frontend.demodulator_priv = state;

	mutex_init(&state->hab_mutex);

	if ((ret = bcm3510_readB(state,0xe0,&v)) < 0)
		goto error;

	deb_info("Revision: 0x%1x, Layer: 0x%1x.\n",v.REVID_e0.REV,v.REVID_e0.LAYER);

	if ((v.REVID_e0.REV != 0x1 && v.REVID_e0.LAYER != 0xb) && /* cold */
		(v.REVID_e0.REV != 0x8 && v.REVID_e0.LAYER != 0x0))   /* warm */
		goto error;

	info("Revision: 0x%1x, Layer: 0x%1x.",v.REVID_e0.REV,v.REVID_e0.LAYER);

	bcm3510_reset(state);

	return &state->frontend;

error:
	kfree(state);
	return NULL;
}