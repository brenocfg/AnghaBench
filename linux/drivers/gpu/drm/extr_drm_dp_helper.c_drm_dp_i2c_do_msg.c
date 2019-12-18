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
struct drm_dp_aux_msg {int reply; int size; } ;
struct drm_dp_aux {int (* transfer ) (struct drm_dp_aux*,struct drm_dp_aux_msg*) ;int /*<<< orphan*/  i2c_defer_count; int /*<<< orphan*/  i2c_nack_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUX_RETRY_INTERVAL ; 
#define  DP_AUX_I2C_REPLY_ACK 133 
#define  DP_AUX_I2C_REPLY_DEFER 132 
 int DP_AUX_I2C_REPLY_MASK ; 
#define  DP_AUX_I2C_REPLY_NACK 131 
#define  DP_AUX_NATIVE_REPLY_ACK 130 
#define  DP_AUX_NATIVE_REPLY_DEFER 129 
 int DP_AUX_NATIVE_REPLY_MASK ; 
#define  DP_AUX_NATIVE_REPLY_NACK 128 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS_RATELIMITED (char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int EBUSY ; 
 int EREMOTEIO ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  dp_aux_i2c_speed_khz ; 
 int /*<<< orphan*/  drm_dp_i2c_msg_write_status_update (struct drm_dp_aux_msg*) ; 
 int /*<<< orphan*/  drm_dp_i2c_retry_count (struct drm_dp_aux_msg*,int /*<<< orphan*/ ) ; 
 int max (int,int /*<<< orphan*/ ) ; 
 int stub1 (struct drm_dp_aux*,struct drm_dp_aux_msg*) ; 
 int /*<<< orphan*/  usleep_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int drm_dp_i2c_do_msg(struct drm_dp_aux *aux, struct drm_dp_aux_msg *msg)
{
	unsigned int retry, defer_i2c;
	int ret;
	/*
	 * DP1.2 sections 2.7.7.1.5.6.1 and 2.7.7.1.6.6.1: A DP Source device
	 * is required to retry at least seven times upon receiving AUX_DEFER
	 * before giving up the AUX transaction.
	 *
	 * We also try to account for the i2c bus speed.
	 */
	int max_retries = max(7, drm_dp_i2c_retry_count(msg, dp_aux_i2c_speed_khz));

	for (retry = 0, defer_i2c = 0; retry < (max_retries + defer_i2c); retry++) {
		ret = aux->transfer(aux, msg);
		if (ret < 0) {
			if (ret == -EBUSY)
				continue;

			/*
			 * While timeouts can be errors, they're usually normal
			 * behavior (for instance, when a driver tries to
			 * communicate with a non-existant DisplayPort device).
			 * Avoid spamming the kernel log with timeout errors.
			 */
			if (ret == -ETIMEDOUT)
				DRM_DEBUG_KMS_RATELIMITED("transaction timed out\n");
			else
				DRM_DEBUG_KMS("transaction failed: %d\n", ret);

			return ret;
		}


		switch (msg->reply & DP_AUX_NATIVE_REPLY_MASK) {
		case DP_AUX_NATIVE_REPLY_ACK:
			/*
			 * For I2C-over-AUX transactions this isn't enough, we
			 * need to check for the I2C ACK reply.
			 */
			break;

		case DP_AUX_NATIVE_REPLY_NACK:
			DRM_DEBUG_KMS("native nack (result=%d, size=%zu)\n", ret, msg->size);
			return -EREMOTEIO;

		case DP_AUX_NATIVE_REPLY_DEFER:
			DRM_DEBUG_KMS("native defer\n");
			/*
			 * We could check for I2C bit rate capabilities and if
			 * available adjust this interval. We could also be
			 * more careful with DP-to-legacy adapters where a
			 * long legacy cable may force very low I2C bit rates.
			 *
			 * For now just defer for long enough to hopefully be
			 * safe for all use-cases.
			 */
			usleep_range(AUX_RETRY_INTERVAL, AUX_RETRY_INTERVAL + 100);
			continue;

		default:
			DRM_ERROR("invalid native reply %#04x\n", msg->reply);
			return -EREMOTEIO;
		}

		switch (msg->reply & DP_AUX_I2C_REPLY_MASK) {
		case DP_AUX_I2C_REPLY_ACK:
			/*
			 * Both native ACK and I2C ACK replies received. We
			 * can assume the transfer was successful.
			 */
			if (ret != msg->size)
				drm_dp_i2c_msg_write_status_update(msg);
			return ret;

		case DP_AUX_I2C_REPLY_NACK:
			DRM_DEBUG_KMS("I2C nack (result=%d, size=%zu)\n",
				      ret, msg->size);
			aux->i2c_nack_count++;
			return -EREMOTEIO;

		case DP_AUX_I2C_REPLY_DEFER:
			DRM_DEBUG_KMS("I2C defer\n");
			/* DP Compliance Test 4.2.2.5 Requirement:
			 * Must have at least 7 retries for I2C defers on the
			 * transaction to pass this test
			 */
			aux->i2c_defer_count++;
			if (defer_i2c < 7)
				defer_i2c++;
			usleep_range(AUX_RETRY_INTERVAL, AUX_RETRY_INTERVAL + 100);
			drm_dp_i2c_msg_write_status_update(msg);

			continue;

		default:
			DRM_ERROR("invalid I2C reply %#04x\n", msg->reply);
			return -EREMOTEIO;
		}
	}

	DRM_DEBUG_KMS("too many retries, giving up\n");
	return -EREMOTEIO;
}