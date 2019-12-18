#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  caps; } ;
struct TYPE_11__ {TYPE_1__ info; } ;
struct TYPE_13__ {TYPE_2__ ops; } ;
struct stv090x_state {scalar_t__ demod_mode; scalar_t__ device; TYPE_6__* internal; TYPE_3__* config; TYPE_4__ frontend; int /*<<< orphan*/  i2c; } ;
struct stv090x_dev {TYPE_6__* internal; } ;
struct TYPE_14__ {int num_used; int dev_ver; int /*<<< orphan*/  tuner_lock; int /*<<< orphan*/  demod_lock; int /*<<< orphan*/  i2c_addr; int /*<<< orphan*/  i2c_adap; scalar_t__ mclk; } ;
struct TYPE_12__ {int /*<<< orphan*/  demod; int /*<<< orphan*/  set_gpio; scalar_t__ diseqc_envelope_mode; int /*<<< orphan*/  address; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FE_CAN_MULTISTREAM ; 
 int /*<<< orphan*/  FE_ERROR ; 
 int /*<<< orphan*/  FE_INFO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SEC_MINI_A ; 
 scalar_t__ STV0900 ; 
 scalar_t__ STV090x_DUAL ; 
 struct stv090x_dev* append_internal (TYPE_6__*) ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int,char*,...) ; 
 struct stv090x_dev* find_dev (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_6__*) ; 
 TYPE_6__* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_dev (TYPE_6__*) ; 
 int /*<<< orphan*/  stv090x_send_diseqc_burst (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stv090x_set_gpio ; 
 scalar_t__ stv090x_setup (TYPE_4__*) ; 

__attribute__((used)) static int stv090x_setup_compound(struct stv090x_state *state)
{
	struct stv090x_dev *temp_int;

	temp_int = find_dev(state->i2c,
			    state->config->address);

	if (temp_int && state->demod_mode == STV090x_DUAL) {
		state->internal = temp_int->internal;
		state->internal->num_used++;
		dprintk(FE_INFO, 1, "Found Internal Structure!");
	} else {
		state->internal = kmalloc(sizeof(*state->internal), GFP_KERNEL);
		if (!state->internal)
			goto error;
		temp_int = append_internal(state->internal);
		if (!temp_int) {
			kfree(state->internal);
			goto error;
		}
		state->internal->num_used = 1;
		state->internal->mclk = 0;
		state->internal->dev_ver = 0;
		state->internal->i2c_adap = state->i2c;
		state->internal->i2c_addr = state->config->address;
		dprintk(FE_INFO, 1, "Create New Internal Structure!");

		mutex_init(&state->internal->demod_lock);
		mutex_init(&state->internal->tuner_lock);

		if (stv090x_setup(&state->frontend) < 0) {
			dprintk(FE_ERROR, 1, "Error setting up device");
			goto err_remove;
		}
	}

	if (state->internal->dev_ver >= 0x30)
		state->frontend.ops.info.caps |= FE_CAN_MULTISTREAM;

	/* workaround for stuck DiSEqC output */
	if (state->config->diseqc_envelope_mode)
		stv090x_send_diseqc_burst(&state->frontend, SEC_MINI_A);

	state->config->set_gpio = stv090x_set_gpio;

	dprintk(FE_ERROR, 1, "Probing %s demodulator(%d) Cut=0x%02x",
		state->device == STV0900 ? "STV0900" : "STV0903",
		state->config->demod,
		state->internal->dev_ver);

	return 0;

error:
	return -ENOMEM;
err_remove:
	remove_dev(state->internal);
	kfree(state->internal);
	return -ENODEV;
}