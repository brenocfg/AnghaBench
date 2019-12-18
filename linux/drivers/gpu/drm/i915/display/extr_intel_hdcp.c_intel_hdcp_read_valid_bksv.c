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
typedef  int /*<<< orphan*/  u8 ;
struct intel_hdcp_shim {int (* read_bksv ) (struct intel_digital_port*,int /*<<< orphan*/ *) ;} ;
struct intel_digital_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int ENODEV ; 
 scalar_t__ intel_hdcp_is_ksv_valid (int /*<<< orphan*/ *) ; 
 int stub1 (struct intel_digital_port*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
int intel_hdcp_read_valid_bksv(struct intel_digital_port *intel_dig_port,
			       const struct intel_hdcp_shim *shim, u8 *bksv)
{
	int ret, i, tries = 2;

	/* HDCP spec states that we must retry the bksv if it is invalid */
	for (i = 0; i < tries; i++) {
		ret = shim->read_bksv(intel_dig_port, bksv);
		if (ret)
			return ret;
		if (intel_hdcp_is_ksv_valid(bksv))
			break;
	}
	if (i == tries) {
		DRM_DEBUG_KMS("Bksv is invalid\n");
		return -ENODEV;
	}

	return 0;
}