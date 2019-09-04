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
typedef  size_t u8 ;
struct psb_intel_sdvo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 size_t SDVO_CMD_STATUS_PENDING ; 
 size_t SDVO_CMD_STATUS_SCALING_NOT_SUPP ; 
 size_t SDVO_CMD_STATUS_SUCCESS ; 
 size_t SDVO_CMD_STATUS_TARGET_NOT_SPECIFIED ; 
 scalar_t__ SDVO_I2C_CMD_STATUS ; 
 scalar_t__ SDVO_I2C_RETURN_0 ; 
 int /*<<< orphan*/  SDVO_NAME (struct psb_intel_sdvo*) ; 
 int /*<<< orphan*/ * cmd_status_names ; 
 int /*<<< orphan*/  psb_intel_sdvo_read_byte (struct psb_intel_sdvo*,scalar_t__,size_t*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static bool psb_intel_sdvo_read_response(struct psb_intel_sdvo *psb_intel_sdvo,
				     void *response, int response_len)
{
	u8 retry = 5;
	u8 status;
	int i;

	DRM_DEBUG_KMS("%s: R: ", SDVO_NAME(psb_intel_sdvo));

	/*
	 * The documentation states that all commands will be
	 * processed within 15µs, and that we need only poll
	 * the status byte a maximum of 3 times in order for the
	 * command to be complete.
	 *
	 * Check 5 times in case the hardware failed to read the docs.
	 */
	if (!psb_intel_sdvo_read_byte(psb_intel_sdvo,
				  SDVO_I2C_CMD_STATUS,
				  &status))
		goto log_fail;

	while ((status == SDVO_CMD_STATUS_PENDING ||
		status == SDVO_CMD_STATUS_TARGET_NOT_SPECIFIED) && retry--) {
		udelay(15);
		if (!psb_intel_sdvo_read_byte(psb_intel_sdvo,
					  SDVO_I2C_CMD_STATUS,
					  &status))
			goto log_fail;
	}

	if (status <= SDVO_CMD_STATUS_SCALING_NOT_SUPP)
		DRM_DEBUG_KMS("(%s)", cmd_status_names[status]);
	else
		DRM_DEBUG_KMS("(??? %d)", status);

	if (status != SDVO_CMD_STATUS_SUCCESS)
		goto log_fail;

	/* Read the command response */
	for (i = 0; i < response_len; i++) {
		if (!psb_intel_sdvo_read_byte(psb_intel_sdvo,
					  SDVO_I2C_RETURN_0 + i,
					  &((u8 *)response)[i]))
			goto log_fail;
		DRM_DEBUG_KMS(" %02X", ((u8 *)response)[i]);
	}
	DRM_DEBUG_KMS("\n");
	return true;

log_fail:
	DRM_DEBUG_KMS("... failed\n");
	return false;
}