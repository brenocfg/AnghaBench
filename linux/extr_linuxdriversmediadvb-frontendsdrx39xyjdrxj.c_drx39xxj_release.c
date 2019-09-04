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
struct dvb_frontend {scalar_t__ exit; struct drx_demod_instance* demodulator_priv; } ;
struct drx_demod_instance {int /*<<< orphan*/  firmware; struct drx_demod_instance* my_i2c_dev_addr; struct drx_demod_instance* my_common_attr; struct drx_demod_instance* my_ext_attr; struct drx_demod_instance* demod; } ;
struct drx39xxj_state {int /*<<< orphan*/  firmware; struct drx39xxj_state* my_i2c_dev_addr; struct drx39xxj_state* my_common_attr; struct drx39xxj_state* my_ext_attr; struct drx39xxj_state* demod; } ;

/* Variables and functions */
 scalar_t__ DVB_FE_DEVICE_REMOVED ; 
 int /*<<< orphan*/  drxj_close (struct drx_demod_instance*) ; 
 int /*<<< orphan*/  kfree (struct drx_demod_instance*) ; 
 int /*<<< orphan*/  release_firmware (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void drx39xxj_release(struct dvb_frontend *fe)
{
	struct drx39xxj_state *state = fe->demodulator_priv;
	struct drx_demod_instance *demod = state->demod;

	/* if device is removed don't access it */
	if (fe->exit != DVB_FE_DEVICE_REMOVED)
		drxj_close(demod);

	kfree(demod->my_ext_attr);
	kfree(demod->my_common_attr);
	kfree(demod->my_i2c_dev_addr);
	release_firmware(demod->firmware);
	kfree(demod);
	kfree(state);
}