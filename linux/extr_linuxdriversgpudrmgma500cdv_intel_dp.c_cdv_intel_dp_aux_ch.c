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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_2__ {struct drm_device* dev; } ;
struct gma_encoder {TYPE_1__ base; struct cdv_intel_dp* dev_priv; } ;
struct drm_device {int dummy; } ;
struct cdv_intel_dp {int output_reg; } ;

/* Variables and functions */
 int DP_AUX_CH_CTL_BIT_CLOCK_2X_SHIFT ; 
 int DP_AUX_CH_CTL_DONE ; 
 int DP_AUX_CH_CTL_MESSAGE_SIZE_MASK ; 
 int DP_AUX_CH_CTL_MESSAGE_SIZE_SHIFT ; 
 int DP_AUX_CH_CTL_PRECHARGE_2US_SHIFT ; 
 int DP_AUX_CH_CTL_RECEIVE_ERROR ; 
 int DP_AUX_CH_CTL_SEND_BUSY ; 
 int DP_AUX_CH_CTL_TIME_OUT_400us ; 
 int DP_AUX_CH_CTL_TIME_OUT_ERROR ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int EBUSY ; 
 int EIO ; 
 int ETIMEDOUT ; 
 int REG_READ (int) ; 
 int /*<<< orphan*/  REG_WRITE (int,int) ; 
 scalar_t__ is_edp (struct gma_encoder*) ; 
 int pack_aux (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  unpack_aux (int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
cdv_intel_dp_aux_ch(struct gma_encoder *encoder,
		uint8_t *send, int send_bytes,
		uint8_t *recv, int recv_size)
{
	struct cdv_intel_dp *intel_dp = encoder->dev_priv;
	uint32_t output_reg = intel_dp->output_reg;
	struct drm_device *dev = encoder->base.dev;
	uint32_t ch_ctl = output_reg + 0x10;
	uint32_t ch_data = ch_ctl + 4;
	int i;
	int recv_bytes;
	uint32_t status;
	uint32_t aux_clock_divider;
	int try, precharge;

	/* The clock divider is based off the hrawclk,
	 * and would like to run at 2MHz. So, take the
	 * hrawclk value and divide by 2 and use that
	 * On CDV platform it uses 200MHz as hrawclk.
	 *
	 */
	aux_clock_divider = 200 / 2;

	precharge = 4;
	if (is_edp(encoder))
		precharge = 10;

	if (REG_READ(ch_ctl) & DP_AUX_CH_CTL_SEND_BUSY) {
		DRM_ERROR("dp_aux_ch not started status 0x%08x\n",
			  REG_READ(ch_ctl));
		return -EBUSY;
	}

	/* Must try at least 3 times according to DP spec */
	for (try = 0; try < 5; try++) {
		/* Load the send data into the aux channel data registers */
		for (i = 0; i < send_bytes; i += 4)
			REG_WRITE(ch_data + i,
				   pack_aux(send + i, send_bytes - i));
	
		/* Send the command and wait for it to complete */
		REG_WRITE(ch_ctl,
			   DP_AUX_CH_CTL_SEND_BUSY |
			   DP_AUX_CH_CTL_TIME_OUT_400us |
			   (send_bytes << DP_AUX_CH_CTL_MESSAGE_SIZE_SHIFT) |
			   (precharge << DP_AUX_CH_CTL_PRECHARGE_2US_SHIFT) |
			   (aux_clock_divider << DP_AUX_CH_CTL_BIT_CLOCK_2X_SHIFT) |
			   DP_AUX_CH_CTL_DONE |
			   DP_AUX_CH_CTL_TIME_OUT_ERROR |
			   DP_AUX_CH_CTL_RECEIVE_ERROR);
		for (;;) {
			status = REG_READ(ch_ctl);
			if ((status & DP_AUX_CH_CTL_SEND_BUSY) == 0)
				break;
			udelay(100);
		}
	
		/* Clear done status and any errors */
		REG_WRITE(ch_ctl,
			   status |
			   DP_AUX_CH_CTL_DONE |
			   DP_AUX_CH_CTL_TIME_OUT_ERROR |
			   DP_AUX_CH_CTL_RECEIVE_ERROR);
		if (status & DP_AUX_CH_CTL_DONE)
			break;
	}

	if ((status & DP_AUX_CH_CTL_DONE) == 0) {
		DRM_ERROR("dp_aux_ch not done status 0x%08x\n", status);
		return -EBUSY;
	}

	/* Check for timeout or receive error.
	 * Timeouts occur when the sink is not connected
	 */
	if (status & DP_AUX_CH_CTL_RECEIVE_ERROR) {
		DRM_ERROR("dp_aux_ch receive error status 0x%08x\n", status);
		return -EIO;
	}

	/* Timeouts occur when the device isn't connected, so they're
	 * "normal" -- don't fill the kernel log with these */
	if (status & DP_AUX_CH_CTL_TIME_OUT_ERROR) {
		DRM_DEBUG_KMS("dp_aux_ch timeout status 0x%08x\n", status);
		return -ETIMEDOUT;
	}

	/* Unload any bytes sent back from the other side */
	recv_bytes = ((status & DP_AUX_CH_CTL_MESSAGE_SIZE_MASK) >>
		      DP_AUX_CH_CTL_MESSAGE_SIZE_SHIFT);
	if (recv_bytes > recv_size)
		recv_bytes = recv_size;
	
	for (i = 0; i < recv_bytes; i += 4)
		unpack_aux(REG_READ(ch_data + i),
			   recv + i, recv_bytes - i);

	return recv_bytes;
}