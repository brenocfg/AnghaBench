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
struct i2c_msg {unsigned int len; int /*<<< orphan*/ * buf; int /*<<< orphan*/  addr; } ;
struct i2c_adapter {struct drm_dp_aux* algo_data; } ;
struct drm_dp_aux_msg {scalar_t__ size; int /*<<< orphan*/ * buffer; int /*<<< orphan*/  request; int /*<<< orphan*/  address; } ;
struct drm_dp_aux {int dummy; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  DP_AUX_I2C_MOT ; 
 int /*<<< orphan*/  DP_AUX_MAX_PAYLOAD_BYTES ; 
 unsigned int clamp (unsigned int,int,int /*<<< orphan*/ ) ; 
 unsigned int dp_aux_i2c_transfer_size ; 
 int drm_dp_i2c_do_msg (struct drm_dp_aux*,struct drm_dp_aux_msg*) ; 
 int drm_dp_i2c_drain_msg (struct drm_dp_aux*,struct drm_dp_aux_msg*) ; 
 int /*<<< orphan*/  drm_dp_i2c_msg_set_request (struct drm_dp_aux_msg*,struct i2c_msg*) ; 
 int /*<<< orphan*/  memset (struct drm_dp_aux_msg*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ min (unsigned int,unsigned int) ; 

__attribute__((used)) static int drm_dp_i2c_xfer(struct i2c_adapter *adapter, struct i2c_msg *msgs,
			   int num)
{
	struct drm_dp_aux *aux = adapter->algo_data;
	unsigned int i, j;
	unsigned transfer_size;
	struct drm_dp_aux_msg msg;
	int err = 0;

	dp_aux_i2c_transfer_size = clamp(dp_aux_i2c_transfer_size, 1, DP_AUX_MAX_PAYLOAD_BYTES);

	memset(&msg, 0, sizeof(msg));

	for (i = 0; i < num; i++) {
		msg.address = msgs[i].addr;
		drm_dp_i2c_msg_set_request(&msg, &msgs[i]);
		/* Send a bare address packet to start the transaction.
		 * Zero sized messages specify an address only (bare
		 * address) transaction.
		 */
		msg.buffer = NULL;
		msg.size = 0;
		err = drm_dp_i2c_do_msg(aux, &msg);

		/*
		 * Reset msg.request in case in case it got
		 * changed into a WRITE_STATUS_UPDATE.
		 */
		drm_dp_i2c_msg_set_request(&msg, &msgs[i]);

		if (err < 0)
			break;
		/* We want each transaction to be as large as possible, but
		 * we'll go to smaller sizes if the hardware gives us a
		 * short reply.
		 */
		transfer_size = dp_aux_i2c_transfer_size;
		for (j = 0; j < msgs[i].len; j += msg.size) {
			msg.buffer = msgs[i].buf + j;
			msg.size = min(transfer_size, msgs[i].len - j);

			err = drm_dp_i2c_drain_msg(aux, &msg);

			/*
			 * Reset msg.request in case in case it got
			 * changed into a WRITE_STATUS_UPDATE.
			 */
			drm_dp_i2c_msg_set_request(&msg, &msgs[i]);

			if (err < 0)
				break;
			transfer_size = err;
		}
		if (err < 0)
			break;
	}
	if (err >= 0)
		err = num;
	/* Send a bare address packet to close out the transaction.
	 * Zero sized messages specify an address only (bare
	 * address) transaction.
	 */
	msg.request &= ~DP_AUX_I2C_MOT;
	msg.buffer = NULL;
	msg.size = 0;
	(void)drm_dp_i2c_do_msg(aux, &msg);

	return err;
}