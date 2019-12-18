#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_9__ ;
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_16__ ;
typedef  struct TYPE_22__   TYPE_15__ ;
typedef  struct TYPE_21__   TYPE_14__ ;
typedef  struct TYPE_20__   TYPE_13__ ;
typedef  struct TYPE_19__   TYPE_12__ ;
typedef  struct TYPE_18__   TYPE_11__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
struct TYPE_23__ {int len; TYPE_15__* stat; } ;
struct TYPE_21__ {int len; TYPE_13__* stat; } ;
struct TYPE_19__ {int len; TYPE_11__* stat; } ;
struct TYPE_17__ {int len; TYPE_9__* stat; } ;
struct TYPE_31__ {int len; TYPE_7__* stat; } ;
struct TYPE_29__ {int len; TYPE_5__* stat; } ;
struct TYPE_27__ {int len; TYPE_3__* stat; } ;
struct TYPE_25__ {int len; TYPE_1__* stat; } ;
struct dtv_frontend_properties {TYPE_16__ cnr; TYPE_14__ block_error; TYPE_12__ block_count; TYPE_10__ post_bit_error; TYPE_8__ post_bit_count; TYPE_6__ pre_bit_error; TYPE_4__ pre_bit_count; TYPE_2__ strength; } ;
struct dvb_frontend {struct dtv_frontend_properties dtv_property_cache; struct i2c_device_addr* demodulator_priv; int /*<<< orphan*/  ops; } ;
struct i2c_device_addr {int verify_microcode; int intermediate_freq; struct dvb_frontend frontend; struct i2c_adapter* i2c; int /*<<< orphan*/  uio_sma_tx_mode; struct i2c_device_addr* my_ext_attr; int /*<<< orphan*/  current_power_mode; struct i2c_device_addr* my_common_attr; int /*<<< orphan*/  microcode_file; struct i2c_device_addr* user_data; struct i2c_device_addr* my_i2c_dev_addr; struct i2c_device_addr* demod; } ;
struct i2c_adapter {int dummy; } ;
struct dvb_frontend_ops {int dummy; } ;
struct drxj_data {int verify_microcode; int intermediate_freq; struct dvb_frontend frontend; struct i2c_adapter* i2c; int /*<<< orphan*/  uio_sma_tx_mode; struct drxj_data* my_ext_attr; int /*<<< orphan*/  current_power_mode; struct drxj_data* my_common_attr; int /*<<< orphan*/  microcode_file; struct drxj_data* user_data; struct drxj_data* my_i2c_dev_addr; struct drxj_data* demod; } ;
struct drx_demod_instance {int verify_microcode; int intermediate_freq; struct dvb_frontend frontend; struct i2c_adapter* i2c; int /*<<< orphan*/  uio_sma_tx_mode; struct drx_demod_instance* my_ext_attr; int /*<<< orphan*/  current_power_mode; struct drx_demod_instance* my_common_attr; int /*<<< orphan*/  microcode_file; struct drx_demod_instance* user_data; struct drx_demod_instance* my_i2c_dev_addr; struct drx_demod_instance* demod; } ;
struct drx_common_attr {int verify_microcode; int intermediate_freq; struct dvb_frontend frontend; struct i2c_adapter* i2c; int /*<<< orphan*/  uio_sma_tx_mode; struct drx_common_attr* my_ext_attr; int /*<<< orphan*/  current_power_mode; struct drx_common_attr* my_common_attr; int /*<<< orphan*/  microcode_file; struct drx_common_attr* user_data; struct drx_common_attr* my_i2c_dev_addr; struct drx_common_attr* demod; } ;
struct drx39xxj_state {int verify_microcode; int intermediate_freq; struct dvb_frontend frontend; struct i2c_adapter* i2c; int /*<<< orphan*/  uio_sma_tx_mode; struct drx39xxj_state* my_ext_attr; int /*<<< orphan*/  current_power_mode; struct drx39xxj_state* my_common_attr; int /*<<< orphan*/  microcode_file; struct drx39xxj_state* user_data; struct drx39xxj_state* my_i2c_dev_addr; struct drx39xxj_state* demod; } ;
struct TYPE_32__ {void* scale; } ;
struct TYPE_30__ {void* scale; } ;
struct TYPE_28__ {void* scale; } ;
struct TYPE_26__ {void* scale; } ;
struct TYPE_24__ {int /*<<< orphan*/  scale; } ;
struct TYPE_22__ {void* scale; } ;
struct TYPE_20__ {void* scale; } ;
struct TYPE_18__ {void* scale; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRX39XX_MAIN_FIRMWARE ; 
 int /*<<< orphan*/  DRX_POWER_DOWN ; 
 int /*<<< orphan*/  DRX_UIO_MODE_READWRITE ; 
 void* FE_SCALE_NOT_AVAILABLE ; 
 int /*<<< orphan*/  FE_SCALE_RELATIVE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  drx39xxj_ops ; 
 int /*<<< orphan*/  drxj_data_g ; 
 int /*<<< orphan*/  drxj_default_addr_g ; 
 int /*<<< orphan*/  drxj_default_comm_attr_g ; 
 int /*<<< orphan*/  drxj_default_demod_g ; 
 int drxj_open (struct i2c_device_addr*) ; 
 int /*<<< orphan*/  kfree (struct i2c_device_addr*) ; 
 struct i2c_device_addr* kmemdup (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct i2c_device_addr* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

struct dvb_frontend *drx39xxj_attach(struct i2c_adapter *i2c)
{
	struct drx39xxj_state *state = NULL;
	struct i2c_device_addr *demod_addr = NULL;
	struct drx_common_attr *demod_comm_attr = NULL;
	struct drxj_data *demod_ext_attr = NULL;
	struct drx_demod_instance *demod = NULL;
	struct dtv_frontend_properties *p;
	int result;

	/* allocate memory for the internal state */
	state = kzalloc(sizeof(struct drx39xxj_state), GFP_KERNEL);
	if (state == NULL)
		goto error;

	demod = kmemdup(&drxj_default_demod_g,
			sizeof(struct drx_demod_instance), GFP_KERNEL);
	if (demod == NULL)
		goto error;

	demod_addr = kmemdup(&drxj_default_addr_g,
			     sizeof(struct i2c_device_addr), GFP_KERNEL);
	if (demod_addr == NULL)
		goto error;

	demod_comm_attr = kmemdup(&drxj_default_comm_attr_g,
				  sizeof(struct drx_common_attr), GFP_KERNEL);
	if (demod_comm_attr == NULL)
		goto error;

	demod_ext_attr = kmemdup(&drxj_data_g, sizeof(struct drxj_data),
				 GFP_KERNEL);
	if (demod_ext_attr == NULL)
		goto error;

	/* setup the state */
	state->i2c = i2c;
	state->demod = demod;

	/* setup the demod data */
	demod->my_i2c_dev_addr = demod_addr;
	demod->my_common_attr = demod_comm_attr;
	demod->my_i2c_dev_addr->user_data = state;
	demod->my_common_attr->microcode_file = DRX39XX_MAIN_FIRMWARE;
	demod->my_common_attr->verify_microcode = true;
	demod->my_common_attr->intermediate_freq = 5000;
	demod->my_common_attr->current_power_mode = DRX_POWER_DOWN;
	demod->my_ext_attr = demod_ext_attr;
	((struct drxj_data *)demod_ext_attr)->uio_sma_tx_mode = DRX_UIO_MODE_READWRITE;
	demod->i2c = i2c;

	result = drxj_open(demod);
	if (result != 0) {
		pr_err("DRX open failed!  Aborting\n");
		goto error;
	}

	/* create dvb_frontend */
	memcpy(&state->frontend.ops, &drx39xxj_ops,
	       sizeof(struct dvb_frontend_ops));

	state->frontend.demodulator_priv = state;

	/* Initialize stats - needed for DVBv5 stats to work */
	p = &state->frontend.dtv_property_cache;
	p->strength.len = 1;
	p->pre_bit_count.len = 1;
	p->pre_bit_error.len = 1;
	p->post_bit_count.len = 1;
	p->post_bit_error.len = 1;
	p->block_count.len = 1;
	p->block_error.len = 1;
	p->cnr.len = 1;

	p->strength.stat[0].scale = FE_SCALE_RELATIVE;
	p->pre_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	p->pre_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	p->post_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	p->post_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	p->block_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	p->block_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	p->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;

	return &state->frontend;

error:
	kfree(demod_ext_attr);
	kfree(demod_comm_attr);
	kfree(demod_addr);
	kfree(demod);
	kfree(state);

	return NULL;
}