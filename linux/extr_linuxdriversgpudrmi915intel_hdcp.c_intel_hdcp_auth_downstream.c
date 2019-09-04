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
typedef  scalar_t__ u8 ;
struct intel_hdcp_shim {int (* read_bstatus ) (struct intel_digital_port*,scalar_t__*) ;int (* read_ksv_fifo ) (struct intel_digital_port*,scalar_t__,scalar_t__*) ;} ;
struct intel_digital_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,scalar_t__) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int /*<<< orphan*/  DRM_HDCP_KSV_LEN ; 
 scalar_t__ DRM_HDCP_MAX_CASCADE_EXCEEDED (scalar_t__) ; 
 scalar_t__ DRM_HDCP_MAX_DEVICE_EXCEEDED (scalar_t__) ; 
 scalar_t__ DRM_HDCP_NUM_DOWNSTREAM (scalar_t__) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int intel_hdcp_poll_ksv_fifo (struct intel_digital_port*,struct intel_hdcp_shim const*) ; 
 int intel_hdcp_validate_v_prime (struct intel_digital_port*,struct intel_hdcp_shim const*,scalar_t__*,scalar_t__,scalar_t__*) ; 
 scalar_t__* kcalloc (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (scalar_t__*) ; 
 int stub1 (struct intel_digital_port*,scalar_t__*) ; 
 int stub2 (struct intel_digital_port*,scalar_t__,scalar_t__*) ; 

__attribute__((used)) static
int intel_hdcp_auth_downstream(struct intel_digital_port *intel_dig_port,
			       const struct intel_hdcp_shim *shim)
{
	u8 bstatus[2], num_downstream, *ksv_fifo;
	int ret, i, tries = 3;

	ret = intel_hdcp_poll_ksv_fifo(intel_dig_port, shim);
	if (ret) {
		DRM_ERROR("KSV list failed to become ready (%d)\n", ret);
		return ret;
	}

	ret = shim->read_bstatus(intel_dig_port, bstatus);
	if (ret)
		return ret;

	if (DRM_HDCP_MAX_DEVICE_EXCEEDED(bstatus[0]) ||
	    DRM_HDCP_MAX_CASCADE_EXCEEDED(bstatus[1])) {
		DRM_ERROR("Max Topology Limit Exceeded\n");
		return -EPERM;
	}

	/*
	 * When repeater reports 0 device count, HDCP1.4 spec allows disabling
	 * the HDCP encryption. That implies that repeater can't have its own
	 * display. As there is no consumption of encrypted content in the
	 * repeater with 0 downstream devices, we are failing the
	 * authentication.
	 */
	num_downstream = DRM_HDCP_NUM_DOWNSTREAM(bstatus[0]);
	if (num_downstream == 0)
		return -EINVAL;

	ksv_fifo = kcalloc(DRM_HDCP_KSV_LEN, num_downstream, GFP_KERNEL);
	if (!ksv_fifo)
		return -ENOMEM;

	ret = shim->read_ksv_fifo(intel_dig_port, num_downstream, ksv_fifo);
	if (ret)
		goto err;

	/*
	 * When V prime mismatches, DP Spec mandates re-read of
	 * V prime atleast twice.
	 */
	for (i = 0; i < tries; i++) {
		ret = intel_hdcp_validate_v_prime(intel_dig_port, shim,
						  ksv_fifo, num_downstream,
						  bstatus);
		if (!ret)
			break;
	}

	if (i == tries) {
		DRM_ERROR("V Prime validation failed.(%d)\n", ret);
		goto err;
	}

	DRM_DEBUG_KMS("HDCP is enabled (%d downstream devices)\n",
		      num_downstream);
	ret = 0;
err:
	kfree(ksv_fifo);
	return ret;
}